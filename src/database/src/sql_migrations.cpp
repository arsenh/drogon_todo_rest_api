#include "sql_migrations.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <fmt/format.h>

void SQLMigrationsPlugin::initAndStart(const Json::Value &config)
{
    LOG_INFO << "Starting SQLMigrationsPlugin";
    try
    {
        const auto& migrations_dir = config["migrations_dir"].asString();
        apply_migrations(migrations_dir);
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "SQL Migration failed, please check config and migration files!: " << e.what();
        exit(-1);
    }
}

void SQLMigrationsPlugin::shutdown()
{
    // nothing to do in shutdown
}

void SQLMigrationsPlugin::apply_migrations(std::string_view migrations_dir)
{
    // create migration table if not exist
    create_migrations_table_if_any();

    // get all migrations from the migration table
    auto appliedMigrations = get_all_migrations_from_table();

    // read, sort .sql migration files from dir and apply
    for (auto files = get_all_migrations_from_dir(migrations_dir); const auto& path : files)
    {
        std::string filename = path.filename().string();

        // check if migration already applied
        if (appliedMigrations.contains(filename)) {
            LOG_INFO << "Skipping already applied: " << filename;
            continue;
        }

        // apply the migration file
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string sql = buffer.str();

        auto dbClient = drogon::app().getDbClient();
        if (!dbClient)
        {
            throw std::runtime_error("DBClient not found!");
        }

        try {
            dbClient->execSqlSync(sql);  // Apply migration
            dbClient->execSqlSync("INSERT INTO migrations (name) VALUES ($1)", filename);  // Record it
            LOG_INFO << "Applied migration: " << filename;
        } catch (const drogon::orm::DrogonDbException &e) {
            LOG_ERROR << "Error applying migration " << filename << ": " << e.base().what();
            throw;
        }
    }
}

void SQLMigrationsPlugin::create_migrations_table_if_any()
{
    auto dbClient = drogon::app().getDbClient();

    if (!dbClient)
    {
        throw std::runtime_error("DBClient not found!");
    }
    try
    {
        dbClient->execSqlSync(R"sql(
        CREATE TABLE IF NOT EXISTS migrations (
            id SERIAL PRIMARY KEY,
            name TEXT UNIQUE NOT NULL,
            applied_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
        );
    )sql");
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_ERROR << "Failed to create migrations table: " << e.base().what();
        throw;
    }
}

std::set<std::string> SQLMigrationsPlugin::get_all_migrations_from_table()
{
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        throw std::runtime_error("DBClient not found!");
    }

    // get all migrations from the migration table
    std::set<std::string> appliedMigrations;
    auto result = dbClient->execSqlSync("SELECT name FROM migrations");
    // get the list all migrations that we have in the migration table
    for (const auto &row : result) {
        appliedMigrations.insert(row["name"].as<std::string>());
    }
    return appliedMigrations;
}

std::vector<std::filesystem::path> SQLMigrationsPlugin::get_all_migrations_from_dir(std::string_view migrations_dir)
{
    std::vector<std::filesystem::path> files;
    for (const auto &entry : std::filesystem::directory_iterator(migrations_dir)) {
        if (entry.path().extension() == ".sql") {
            files.push_back(entry.path());
        }
    }

    std::ranges::sort(files);
    return files;
}
