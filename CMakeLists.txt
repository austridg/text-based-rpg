cmake_minimum_required(VERSION 3.16)

project(text_rpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(buildtool/Utils.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_FILES
	CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_executable(text_rpg ${SRC_FILES})
target_include_directories(text_rpg PRIVATE src)

GroupSourcesByFolder(text_rpg)

target_compile_options(text_rpg PRIVATE -DNOMINMAX)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(text_rpg PRIVATE $<$<CONFIG:Debug>:-g -O0>)
endif()

set_target_properties(text_rpg PROPERTIES OUTPUT_NAME "text_rpg")
