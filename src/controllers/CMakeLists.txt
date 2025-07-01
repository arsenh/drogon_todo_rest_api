add_library(controllers STATIC)

target_sources(controllers
        PRIVATE
        src/todo_controller.cpp
        PUBLIC
        include/todo_controller.hpp
)


target_link_libraries(controllers PUBLIC data database fmt::fmt Drogon::Drogon)

target_include_directories(controllers PUBLIC include)

