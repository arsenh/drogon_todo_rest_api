add_library(server STATIC)

target_sources(server PRIVATE src/server.cpp src/todoController.cpp)

target_link_libraries(server PRIVATE fmt::fmt Drogon::Drogon)

target_include_directories(server PUBLIC include)

