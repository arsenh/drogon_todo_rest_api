#pragma once
#include <string>
#include <utility>

class Server
{
public:
    Server()
        :   mAddr{"0.0.0.0"},
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
