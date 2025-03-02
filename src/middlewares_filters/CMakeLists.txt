add_library(middlewares_filters STATIC)

target_sources(middlewares_filters PRIVATE src/request_log.cpp)

target_link_libraries(middlewares_filters PUBLIC fmt::fmt Drogon::Drogon)

target_include_directories(middlewares_filters PUBLIC include)

