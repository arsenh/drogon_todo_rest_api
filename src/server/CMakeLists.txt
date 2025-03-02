add_library(server STATIC)

target_sources(server PRIVATE src/server.cpp)

target_link_libraries(server PUBLIC  middlewares_filters controllers fmt::fmt Drogon::Drogon)

target_include_directories(server PUBLIC include)

