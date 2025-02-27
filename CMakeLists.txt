cmake_minimum_required(VERSION 3.16)
project(todo_api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(fmt REQUIRED)
find_package(Drogon REQUIRED)


# Add subdirectories (static libraries)
add_subdirectory(src/server)

# Define the executable
add_executable(todo_api src/main.cpp)

# Link libraries to the executable
target_link_libraries(todo_api PRIVATE server fmt::fmt Drogon::Drogon)

