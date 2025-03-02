#include "server.hpp"

#include <drogon/drogon.h>

//The following headers are required for automatic detection of controllers and filters
#include "todoController.hpp"
#include "request_log.hpp"

void Server::run() const
{
    LOG_INFO << "Server started...";

    drogon::app().setLogPath("")
     .setLogLevel(trantor::Logger::kDebug)
     .addListener(mAddr, mPort)
     .setThreadNum(2)
     .run();
}
