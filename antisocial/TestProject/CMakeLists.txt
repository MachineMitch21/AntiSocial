cmake_minimum_required(VERSION 3.5)

project(proj-test)

file(GLOB SOURCES src/*.cpp)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}../build)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/../include ${PROJECT_SOURCE_DIR}/../external)
find_library(ASLIB antisocial)

if (UNIX)
target_link_libraries(${PROJECT_NAME} ${ASLIB} GL GLEW)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} ${ASLIB} glew32 glfw3dll opengl32 kernel32 user32)
endif (WIN32)
