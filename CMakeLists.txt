cmake_minimum_required(VERSION 3.10)
project(HeavenFortress)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependencies
if(WIN32)
    find_package(OpenGL REQUIRED)
else()
    # Manual fallback for Linux: directly link generic GL/GLU libraries
    # This avoids FindOpenGL failures on some Ubuntu environments
    message(STATUS "Using generic GL/GLU libraries for Linux")
    set(OPENGL_LIBRARIES GL GLU)
    set(OPENGL_FOUND TRUE)
endif()
if(WIN32)
    find_package(GLEW REQUIRED)
else()
    # Use PkgConfig to find GLEW on Linux
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PKG_GLEW REQUIRED glew)
    
    # Create the expected target manually using PkgConfig results
    add_library(GLEW::GLEW INTERFACE IMPORTED)
    target_link_libraries(GLEW::GLEW INTERFACE ${PKG_GLEW_LIBRARIES})
    target_include_directories(GLEW::GLEW INTERFACE ${PKG_GLEW_INCLUDE_DIRS})
    target_compile_options(GLEW::GLEW INTERFACE ${PKG_GLEW_CFLAGS_OTHER})
endif()

if(WIN32)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
else()
    # Manual fallback for Linux: directly link standard SDL2 libraries
    message(STATUS "Using generic SDL2 libraries for Linux")
    set(SDL2_LIBRARIES SDL2)
    set(SDL2_MIXER_LIBRARIES SDL2_mixer)
    
    # Create imported targets to satisfy target_link_libraries downstream
    add_library(SDL2::SDL2 INTERFACE IMPORTED)
    target_link_libraries(SDL2::SDL2 INTERFACE SDL2)
    
    add_library(SDL2_mixer::SDL2_mixer INTERFACE IMPORTED)
    target_link_libraries(SDL2_mixer::SDL2_mixer INTERFACE SDL2_mixer)
endif()
if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DNOMINMAX)
endif()
if(WIN32)
    find_package(freeglut CONFIG)
    if(NOT freeglut_FOUND)
        find_package(GLUT REQUIRED)
    endif()
elseif(NOT APPLE)
    # Manual fallback for GLUT on Linux
    message(STATUS "Using generic GLUT library for Linux")
    set(GLUT_INCLUDE_DIRS /usr/include)
    set(GLUT_LIBRARIES glut)
    set(GLUT_FOUND TRUE)
endif()
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
endif()

# Include directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    .
)

if(APPLE)
    # macOS specific frameworks
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
else()
    include_directories(${GLUT_INCLUDE_DIRS})
endif()

# --- Client ---
add_executable(HeavensFortressClient
    client.cpp
    Game.cpp
    func.cpp
    Scene_Animation.cpp
    motionController.cpp
    Scene_Title.cpp
    Collision.cpp
    Init.cpp
    InputController.cpp
    Scene_Shooting.cpp
    Scene_Chess.cpp
    Scene_Entrance.cpp
    Scene_Park.cpp
    Scene_Race.cpp
    Scene_Tank.cpp
    struc.cpp
)

target_link_libraries(HeavensFortressClient
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>
)

if(APPLE)
    target_link_libraries(HeavensFortressClient "-framework GLUT" ${COREVIDEO_LIBRARY} ${IOKIT_LIBRARY} ${COCOA_LIBRARY})
else()
    if(WIN32 AND TARGET freeglut::freeglut)
        target_link_libraries(HeavensFortressClient freeglut::freeglut)
    elseif(WIN32 AND TARGET freeglut::freeglut_static)
        target_link_libraries(HeavensFortressClient freeglut::freeglut_static)
    else()
        target_link_libraries(HeavensFortressClient ${GLUT_LIBRARIES})
    endif()
endif()

if(WIN32)
    target_link_libraries(HeavensFortressClient ws2_32)
    target_compile_definitions(HeavensFortressClient PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS FREEGLUT_LIB_PRAGMAS=0 SDL_MAIN_HANDLED)
    # Suppress truncation and conversion warnings
    target_compile_options(HeavensFortressClient PRIVATE /wd4244 /wd4305 /wd4996 /wd5208 /wd4267 /utf-8)
endif()

# --- Server ---
add_executable(HeavensFortressServer
    server/main.cpp
    server/server.cpp
)
target_include_directories(HeavensFortressServer PRIVATE .)

if(WIN32)
    target_link_libraries(HeavensFortressServer ws2_32)
    target_compile_definitions(HeavensFortressServer PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS SERVER_BUILD)
    target_compile_options(HeavensFortressServer PRIVATE /wd4244 /wd4305 /wd4996 /wd5208 /wd4267 /utf-8)
else()
    target_compile_definitions(HeavensFortressServer PRIVATE SERVER_BUILD)
endif()

# --- Packaging ---
set(CPACK_PACKAGE_NAME "HeavensFortress")
set(CPACK_PACKAGE_VENDOR "Teru0822")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Heaven's Fortress Game")
set(CPACK_PACKAGE_CONTACT "teru0822@example.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

if(WIN32)
    find_program(NSIS_MAKENSIS makensis)
    if(NSIS_MAKENSIS)
        set(CPACK_GENERATOR "NSIS")
    else()
        message(WARNING "NSIS not found, falling back to ZIP generator")
        set(CPACK_GENERATOR "ZIP")
    endif()
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ;DEB")
endif()

# Install rules
install(TARGETS HeavensFortressClient HeavensFortressServer DESTINATION bin)
install(DIRECTORY config DESTINATION bin)

if(WIN32)
    # Attempt to find the directory containing runtime DLLs from SDL2_mixer target
    get_target_property(SDL2_MIXER_LIB SDL2_mixer::SDL2_mixer IMPORTED_LOCATION_RELEASE)
    if(NOT SDL2_MIXER_LIB)
        get_target_property(SDL2_MIXER_LIB SDL2_mixer::SDL2_mixer IMPORTED_LOCATION)
    endif()

    if(SDL2_MIXER_LIB)
        get_filename_component(DLL_SEARCH_DIR "${SDL2_MIXER_LIB}" DIRECTORY)
        message(STATUS "Searching for DLLs in: ${DLL_SEARCH_DIR}")
        
        # Glob all DLLs in dependency directory (catch wavpack, vorbis, etc.)
        file(GLOB ALL_DEP_DLLS "${DLL_SEARCH_DIR}/*.dll")
        
        # If no DLLs found, check if we are in lib dir and try ../bin
        if(NOT ALL_DEP_DLLS)
            get_filename_component(PARENT_DIR "${DLL_SEARCH_DIR}" DIRECTORY)
            set(BIN_SEARCH_DIR "${PARENT_DIR}/bin")
            message(STATUS "No DLLs found in ${DLL_SEARCH_DIR}. Trying ${BIN_SEARCH_DIR}")
            file(GLOB ALL_DEP_DLLS "${BIN_SEARCH_DIR}/*.dll")
        endif()
        
        # Install all found DLLs
        install(FILES ${ALL_DEP_DLLS} DESTINATION bin)
        
        # Copy for local run
        foreach(DLL_FILE ${ALL_DEP_DLLS})
             add_custom_command(TARGET HeavensFortressClient POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DLL_FILE}"
                $<TARGET_FILE_DIR:HeavensFortressClient>
            )
        endforeach()
    else()
        # Fallback if target property fails (unlikely with vcpkg)
        message(WARNING "Could not determine SDL2_mixer DLL path. Falling back to explicit list.")
        install(FILES $<TARGET_FILE:SDL2::SDL2> 
                      $<TARGET_FILE:SDL2_mixer::SDL2_mixer> 
                      $<TARGET_FILE:GLEW::GLEW> 
                DESTINATION bin)
    endif()
endif()

include(CPack)
