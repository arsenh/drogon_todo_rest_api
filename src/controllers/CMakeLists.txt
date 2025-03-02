add_library(controllers STATIC
        include/todoController.hpp)

target_sources(controllers PRIVATE src/todoController.cpp)

target_link_libraries(controllers PRIVATE fmt::fmt Drogon::Drogon)

target_include_directories(controllers PUBLIC include)

