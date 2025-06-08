#pragma once

#include <drogon/drogon.h>
#include <drogon/plugins/Plugin.h>
#include <drogon/HttpAppFramework.h>

#include <filesystem>
#include <string_view>
#include <set>
#include <vector>

class SQLMigrationsPlugin final : public drogon::Plugin<SQLMigrationsPlugin> {
public:
    // drogon forces explicit declaration of default constructor
    SQLMigrationsPlugin() {}
    void initAndStart(const Json::Value& config) override;
    void shutdown() override;
private:
    static void apply_migrations(std::string_view migrations_dir);
    static void create_migrations_table_if_any();
    static std::set<std::string> get_all_migrations_from_table();
    static std::vector<std::filesystem::path> get_all_migrations_from_dir(std::string_view migrations_dir);
};