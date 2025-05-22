add_library(database STATIC)

target_sources(database
        PRIVATE
        src/mongo_dbrepository.cpp
        PUBLIC
        include/dbcontext.hpp
        include/idbrepository.hpp
        include/mongo_dbrepository.hpp
)
target_link_libraries(database PUBLIC fmt::fmt Drogon::Drogon)

target_include_directories(database PUBLIC include)

