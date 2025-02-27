#include <iostream>
#include "server/include/server.hpp"

#include <fmt/core.h>
#include <drogon/drogon.h>

using namespace drogon;

int main() {
    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kWarn)
         .addListener("0.0.0.0", 8080)
         .setThreadNum(16)
         .run();
    return 0;
}

