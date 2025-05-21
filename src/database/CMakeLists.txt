add_library(database STATIC)

target_sources(database
        PRIVATE
        src/mongodb_manager.cpp
        PUBLIC
        include/mongodb_manager.hpp
)
target_link_libraries(database PUBLIC fmt::fmt Drogon::Drogon)

target_include_directories(database PUBLIC include)

