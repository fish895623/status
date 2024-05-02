cmake_minimum_required(VERSION 3.20)

project(status)


file(GLOB_RECURSE SOURCES sources/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
