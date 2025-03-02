add_library(middlewares_filters STATIC
        include/request_log.hpp)

target_sources(middlewares_filters PRIVATE src/request_log.cpp)

target_link_libraries(middlewares_filters PRIVATE fmt::fmt Drogon::Drogon)

target_include_directories(middlewares_filters PUBLIC include)

