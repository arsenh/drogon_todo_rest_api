add_library(data STATIC)

target_sources(data PRIVATE src/todo.cpp src/todo_service.cpp)
target_sources(controllers
        PRIVATE
        src/todo.cpp
        src/todo_service.cpp
        PUBLIC
        include/todo.hpp
        include/todo_service.hpp
)
target_link_libraries(data PUBLIC database Drogon::Drogon)

target_include_directories(data PUBLIC include)

