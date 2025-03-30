#pragma once

#include "todo_service.hpp"


#include <json/json.h>


class TodoParser {
public:
    static Json::Value todos_to_json(const std::vector<TodoEntity>& todos);
    static std::string time_point_to_ISO8601(const std::chrono::time_point<std::chrono::system_clock>& timePoint);
    static std::chrono::time_point<std::chrono::system_clock> parse_ISO8601(const std::string& timeStr);
};