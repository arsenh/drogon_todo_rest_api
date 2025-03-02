#pragma once

#include <string>
#include <chrono>

struct TodoEntity
{
    int id;
    std::string title;
    std::string description;
    bool completed;
    std::chrono::time_point<std::chrono::system_clock> created_at;
};