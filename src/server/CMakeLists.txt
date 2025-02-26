add_library(server STATIC)

target_sources(server PRIVATE src/server.cpp)

target_include_directories(server PUBLIC include)

