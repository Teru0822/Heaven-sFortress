cmake_minimum_required(VERSION 3.10)
project(HeavenFortress)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependencies
if(WIN32)
    find_package(OpenGL REQUIRED)
else()
    # Direct library paths for Linux (Ubuntu 22.04)
    message(STATUS "Searching for libraries in standard Linux paths...")
    
    # Find actual library files - try multiple names and paths
    find_library(GL_LIB 
        NAMES GL OpenGL
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64
        PATH_SUFFIXES GL)
    find_library(GLU_LIB 
        NAMES GLU
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64
        PATH_SUFFIXES GL)
    
    if(GL_LIB AND GLU_LIB)
        set(OPENGL_LIBRARIES ${GL_LIB} ${GLU_LIB})
        message(STATUS "Found GL: ${GL_LIB}")
        message(STATUS "Found GLU: ${GLU_LIB}")
    else()
        # Try CMake's standard FindOpenGL as last resort
        find_package(OpenGL)
        if(OPENGL_FOUND)
            message(STATUS "Found OpenGL via FindOpenGL module")
        else()
            set(OPENGL_LIBRARIES GL GLU)
            message(WARNING "GL/GLU not found! GL_LIB=${GL_LIB}, GLU_LIB=${GLU_LIB}")
            message(WARNING "Using fallback library names - linking may fail")
        endif()
    endif()
    set(OPENGL_FOUND TRUE)
    include_directories("/usr/include")
endif()
if(WIN32)
    find_package(GLEW REQUIRED)
elseif(UNIX AND NOT APPLE)
    # Direct library path for GLEW on Linux
    find_library(GLEW_LIB NAMES GLEW glew
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64)
    if(GLEW_LIB)
        message(STATUS "Found GLEW: ${GLEW_LIB}")
        add_library(GLEW::GLEW INTERFACE IMPORTED)
        target_link_libraries(GLEW::GLEW INTERFACE ${GLEW_LIB})
        target_include_directories(GLEW::GLEW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    else()
        # Try standard FindGLEW
        find_package(GLEW)
        if(NOT GLEW_FOUND)
            message(WARNING "GLEW not found! GLEW_LIB=${GLEW_LIB}")
            add_library(GLEW::GLEW INTERFACE IMPORTED)
            target_link_libraries(GLEW::GLEW INTERFACE GLEW)
            target_include_directories(GLEW::GLEW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
        endif()
    endif()
    set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

if(WIN32)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
else()
    # Direct library paths for SDL2 on Linux
    find_library(SDL2_LIB NAMES SDL2 SDL2-2.0 
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64)
    find_library(SDL2_MIXER_LIB NAMES SDL2_mixer SDL2_mixer-2.0 
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64)
    
    if(SDL2_LIB)
        message(STATUS "Found SDL2: ${SDL2_LIB}")
        set(SDL2_LIBRARIES ${SDL2_LIB})
    else()
        message(WARNING "SDL2 not found! SDL2_LIB=${SDL2_LIB}")
        set(SDL2_LIBRARIES SDL2)
    endif()
    
    if(SDL2_MIXER_LIB)
        message(STATUS "Found SDL2_mixer: ${SDL2_MIXER_LIB}")
        set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIB})
    else()
        message(WARNING "SDL2_mixer not found! SDL2_MIXER_LIB=${SDL2_MIXER_LIB}")
        set(SDL2_MIXER_LIBRARIES SDL2_mixer)
    endif()

    # Create imported targets
    if(NOT TARGET SDL2::SDL2)
        add_library(SDL2::SDL2 INTERFACE IMPORTED)
        target_link_libraries(SDL2::SDL2 INTERFACE ${SDL2_LIBRARIES})
    endif()
    
    if(NOT TARGET SDL2_mixer::SDL2_mixer)
        add_library(SDL2_mixer::SDL2_mixer INTERFACE IMPORTED)
        target_link_libraries(SDL2_mixer::SDL2_mixer INTERFACE ${SDL2_MIXER_LIBRARIES})
    endif()
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
    # Direct library path for GLUT on Linux
    find_library(GLUT_LIB NAMES glut freeglut
        PATHS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64 /lib/x86_64-linux-gnu /lib /lib64)
    if(GLUT_LIB)
        message(STATUS "Found GLUT: ${GLUT_LIB}")
        set(GLUT_LIBRARIES ${GLUT_LIB})
    else()
        # Try standard FindGLUT
        find_package(GLUT)
        if(NOT GLUT_FOUND)
            message(WARNING "GLUT not found! GLUT_LIB=${GLUT_LIB}")
            set(GLUT_LIBRARIES glut)
        endif()
    endif()
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

# Add local include only on Linux (for GL headers fallback)
if(UNIX AND NOT APPLE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

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
    # Linux packaging
    set(CPACK_GENERATOR "TGZ;DEB")
    
    # DEB-specific settings
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Teru0822 <teru0822@example.com>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-2.0-0, libsdl2-mixer-2.0-0, libglew2.2, freeglut3, libgl1, libglu1-mesa")
    set(CPACK_DEBIAN_PACKAGE_SECTION "games")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/Teru0822/Heaven-sFortress")
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
    
    # Create desktop entry
    set(DESKTOP_FILE "${CMAKE_CURRENT_BINARY_DIR}/HeavensFortress.desktop")
    file(WRITE ${DESKTOP_FILE}
"[Desktop Entry]
Type=Application
Name=Heaven's Fortress
Comment=Heaven's Fortress Game
Exec=/usr/bin/HeavensFortressClient
Icon=heavensfortress
Terminal=false
Categories=Game;
")
    install(FILES ${DESKTOP_FILE} DESTINATION share/applications)
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
