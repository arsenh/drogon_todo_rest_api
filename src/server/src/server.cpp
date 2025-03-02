#include "server.hpp"

#include <drogon/drogon.h>

void Server::run() const
{
    LOG_INFO << "Server started...";

    drogon::app().setLogPath("")
     .setLogLevel(trantor::Logger::kDebug)
     .addListener(mAddr, mPort)
     .setThreadNum(2)
     .run();
}
