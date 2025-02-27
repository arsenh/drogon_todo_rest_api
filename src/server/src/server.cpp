#include "server.hpp"
#include "todoController.h"

#include <drogon/drogon.h>

#include <iostream>
#include <memory>

void Server::run() const
{
    std::cout << "Server starting..." << std::endl;
    auto todo = std::make_shared<TodoController>();

    drogon::app().setLogPath("./")
     .setLogLevel(trantor::Logger::kTrace)
     .addListener(mAddr, mPort)
     .setThreadNum(2)
     .registerController(todo)
     .run();
}
