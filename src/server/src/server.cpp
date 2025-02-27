#include "server.hpp"

#include <drogon/drogon.h>

#include <iostream>

void Server::run() const
{
    std::cout << "Server starting..." << std::endl;
    drogon::app().setLogPath("./")
     .setLogLevel(trantor::Logger::kWarn)
     .addListener(mAddr, mPort)
     .setThreadNum(16)
     .run();

}
