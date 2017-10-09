CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(antisocial)
SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "1")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

file(GLOB SOURCES src/*.cpp src/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_definitions(-DGLEW_STATIC -DGLEW_NO_GLU)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external)
link_directories(${PROJECT_SOURCE_DIR}/lib)

if (UNIX)
target_link_libraries(${PROJECT_NAME} GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt pthread dl)
endif (UNIX)

if (WINDOWS)
target_link_libraries(${PROJECT_NAME} GLEW glfw3 GL)
endif (WINDOWS)
