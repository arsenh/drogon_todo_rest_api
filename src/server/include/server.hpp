#pragma once
//The following headers are required for automatic detection of controllers and filters
#include "todo_controller.hpp"
#include "request_log.hpp"

class Server
{
public:
    Server();
private:
    static bool lead_app_config();
    static bool load_custom_config();
public:
    static void run();
};
