cmake_minimum_required (VERSION 3.14)

project(PolisEngine
	VERSION 0.1.1
	DESCRIPTION "An open-source game engine focusing on ECS and Lua scripting"
	HOMEPAGE_URL "https://github.com/PixelArtDragon/PolisEngine"
	LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

add_subdirectory(src)

add_subdirectory(data)

add_dependencies(PolisEngine copy-data-files)

target_include_directories(PolisEngine PUBLIC third_party/include)
target_include_directories(PolisEngine PRIVATE include)

target_link_directories(PolisEngine PUBLIC third_party/lib/x64)

target_link_libraries(PolisEngine freetype.lib Yoga.lib liblua54.lib opengl32.lib glew32.lib glfw3.lib)

if ( MSVC )
    set_target_properties(PolisEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
    set_target_properties(PolisEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out)
    set_target_properties(PolisEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out)
endif ( MSVC )

configure_file(third_party/dll/x64/glew32.dll ${CMAKE_SOURCE_DIR}/out/glew32.dll COPYONLY)
configure_file(third_party/dll/x64/lua54.dll ${CMAKE_SOURCE_DIR}/out/lua54.dll COPYONLY)

