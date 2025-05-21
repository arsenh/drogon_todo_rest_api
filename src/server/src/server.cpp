#include "server.hpp"

#include <drogon/drogon.h>

#include <string_view>
#include <filesystem>

Server::Server()
{
    using namespace drogon;

    LOG_INFO << "Server starting...";

    if (!lead_app_config())
    {
        LOG_ERROR << "Config file not found!";
        return;
    }

    if (!load_custom_config())
    {
        LOG_ERROR << "Custom config section is null, check config format";
        return;
    }
    if (!connect_mongodb())
    {
        return;
    }
}

bool Server::lead_app_config()
{
    const std::string_view config_file{"./config.json"};
    if (std::filesystem::path config_file_path {config_file}; !std::filesystem::exists(config_file_path))
        return false;
    app().loadConfigFile(config_file.data());
    return true;
}

bool Server::load_custom_config()
{
    const auto& custom_config = app().getCustomConfig();
    return !custom_config.isNull();
}

bool Server::connect_mongodb()
{
    const auto& custom_config = app().getCustomConfig();

    if (!custom_config.isMember("mongodb"))
    {
        LOG_ERROR << "MongoDB config not found in the config file";
        return false;
    }

    const std::string uri = custom_config["mongodb"]["uri"].asString();
    if (uri.empty())
    {
        LOG_ERROR << "MongoDB URI is empty";
        return false;
    }
    const std::string database = custom_config["mongodb"]["database"].asString();
    if (database.empty())
    {
        LOG_ERROR << "MongoDB database is empty";
        return false;
    }
    LOG_INFO << "MongoDB URI: " << uri;
    LOG_INFO << "MongoDB database: " << database;

    //TODO: connect to MondoDB server.

    return true;
}


void Server::run()
{
    app().run();
}
