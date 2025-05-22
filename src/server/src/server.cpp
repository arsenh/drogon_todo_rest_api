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
}

bool Server::lead_app_config()
{
    constexpr std::string_view config_file{"./config.json"};
    if (const std::filesystem::path config_file_path {config_file}; !std::filesystem::exists(config_file_path))
        return false;
    app().loadConfigFile(config_file.data());
    return true;
}

void Server::run()
{
    app().run();
}
