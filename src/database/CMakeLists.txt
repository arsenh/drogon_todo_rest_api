add_library(database STATIC)

target_sources(database
        PRIVATE
        src/pq_dbrepository.cpp
        src/sql_migrations.cpp
        PUBLIC
        include/idbrepository.hpp
        include/pq_dbrepository.hpp
        include/sql_migrations.hpp
)
target_link_libraries(database PUBLIC data fmt::fmt Drogon::Drogon libpqxx::pqxx)

target_include_directories(database PUBLIC include)

