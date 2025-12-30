cmake_minimum_required(VERSION 3.10)
project(HeavenFortress)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DNOMINMAX)
endif()
if(WIN32)
    find_package(freeglut CONFIG)
    if(NOT freeglut_FOUND)
        find_package(GLUT REQUIRED)
    endif()
elseif(NOT APPLE)
    find_package(GLUT REQUIRED)
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
    target_compile_options(HeavensFortressClient PRIVATE /wd4244 /wd4305 /wd4996 /wd5208 /wd4267)

    # Copy DLLs to output directory
    # Copy DLLs to output directory
    add_custom_command(TARGET HeavensFortressClient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE:SDL2_mixer::SDL2_mixer>
            $<TARGET_FILE:GLEW::GLEW>
            $<TARGET_FILE_DIR:HeavensFortressClient>
    )

    if(TARGET freeglut::freeglut)
        add_custom_command(TARGET HeavensFortressClient POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:freeglut::freeglut>
                $<TARGET_FILE_DIR:HeavensFortressClient>
        )
    endif()
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
    target_compile_options(HeavensFortressServer PRIVATE /wd4244 /wd4305 /wd4996 /wd5208 /wd4267)
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
    set(CPACK_GENERATOR "NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ;DEB")
endif()

# Install rules
install(TARGETS HeavensFortressClient HeavensFortressServer DESTINATION bin)
install(DIRECTORY config DESTINATION .)

include(CPack)
