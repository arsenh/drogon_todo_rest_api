#include "server.hpp"

#include <drogon/drogon.h>

void Server::run()
{
    LOG_INFO << "Server started...";

    drogon::app().setLogPath("")
     .setLogLevel(trantor::Logger::kDebug)
     .loadConfigFile("./config.json")
     .run();
}
