#include "server.hpp"

#include <drogon/drogon.h>
#include <json/json.h>

#include <string_view>
#include <filesystem>
#include <fstream>

Server::Server()
{
    using namespace drogon;

    LOG_INFO << "Server starting...";

    if (!lead_app_config())
    {
        LOG_ERROR << "Config file not found!";
        exit(-1);
    }
}

bool Server::lead_app_config()
{
    const std::string& config_file{"./config.json"};

    if (const std::filesystem::path config_file_path {config_file}; !std::filesystem::exists(config_file_path))
        return false;

    // Since Drogon is not yet supported, loading environment variables is required at runtime.
    std::ifstream config_stream{config_file};
    Json::Value config;
    config_stream >> config;

    // Inject sensitive data from environment
    const char* postgres_user = std::getenv("POSTGRES_USER");
    const char* postgres_pass = std::getenv("POSTGRES_PASSWORD");

    if (postgres_user && postgres_pass) {
        config["db_clients"][0]["user"] = postgres_user;
        config["db_clients"][0]["passwd"] = postgres_pass;
    }
    else
    {
        std::cerr << "Environment variables POSTGRES_USER or POSTGRES_PASSWORD not set!" << std::endl;
        return false;
    }

    app().loadConfigJson(config);
    return true;
}

void Server::run()
{
    app().run();
}
