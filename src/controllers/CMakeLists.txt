add_library(controllers STATIC)

target_sources(controllers
        PRIVATE
        src/todoController.cpp
        PUBLIC
        include/todoController.hpp
)


target_link_libraries(controllers PUBLIC data fmt::fmt Drogon::Drogon)

target_include_directories(controllers PUBLIC include)

