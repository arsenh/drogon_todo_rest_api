#include "server.hpp"

#include <drogon/drogon.h>
#include <json/json.h>

#include <filesystem>
#include <fstream>
#include <exception>
#include <string>


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
    const char* postgres_db = std::getenv("POSTGRES_DB");
    const char* postgres_host = std::getenv("POSTGRES_HOST");
    const char* postgres_port = std::getenv("POSTGRES_PORT");

    int port;

    try
    {
        port = std::stoi(std::string(postgres_port));
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid port number: " << postgres_port << std::endl;
        return false;
    }
    if (postgres_user
        && postgres_pass
        && postgres_db
        && postgres_host
        && postgres_port) {
        config["db_clients"][0]["user"] = postgres_user;
        config["db_clients"][0]["passwd"] = postgres_pass;
        config["db_clients"][0]["dbname"] = postgres_db;
        config["db_clients"][0]["host"] = postgres_host;
        config["db_clients"][0]["port"] = port;
    }
    else
    {
        std::cerr << "One of these environment variables is not set (POSTGRES_USER, "
                     "POSTGRES_PASSWORD, POSTGRES_DB, POSTGRES_HOST, POSTGRES_PORT)" << std::endl;
        return false;
    }

    app().loadConfigJson(config);
    return true;
}

void Server::run()
{
    app().run();
}
