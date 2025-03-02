#pragma once
#include <string>
#include <utility>

//The following headers are required for automatic detection of controllers and filters
#include "todoController.hpp"
#include "request_log.hpp"

class Server
{
public:
    Server()
        :   mAddr{"127.0.0.1"},
            mPort{8080}
    {

    }

    Server(std::string  addr, int port)
        :   mAddr{std::move(addr)},
            mPort{port}
    {

    }


    void run() const;
private:
    std::string mAddr;
    int mPort;
};
