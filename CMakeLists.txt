cmake_minimum_required(VERSION 3.16)
project(todo_api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(fmt REQUIRED)
find_package(Drogon REQUIRED)
find_package(Catch2 REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)
file(COPY ${CMAKE_SOURCE_DIR}/static DESTINATION ${CMAKE_BINARY_DIR})

# Add subdirectories (static libraries)
add_subdirectory(src/app)
add_subdirectory(src/server)
add_subdirectory(src/controllers)
add_subdirectory(src/middlewares_filters)
add_subdirectory(src/data)
add_subdirectory(src/unit_tests)