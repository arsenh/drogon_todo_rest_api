add_library(controllers STATIC)

target_sources(controllers
        PRIVATE
        src/todo_controller.cpp
        src/todo_parser.cpp
        PUBLIC
        include/todo_controller.hpp
        include/todo_parser.hpp
)


target_link_libraries(controllers PUBLIC data fmt::fmt Drogon::Drogon)

target_include_directories(controllers PUBLIC include)

