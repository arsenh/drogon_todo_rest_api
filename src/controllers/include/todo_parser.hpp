#pragma once

#include "todo.hpp"

#include <json/json.h>
#include <string>
#include <chrono>
#include <utility>


class TodoParser {
public:
    static Json::Value todos_to_json(const std::vector<TodoEntity>& todos);
    static Json::Value todo_to_json(const TodoEntity& todo);
    static std::string time_point_to_ISO8601(const std::chrono::time_point<std::chrono::system_clock>& timePoint);
    static std::chrono::time_point<std::chrono::system_clock> parse_ISO8601(const std::string& timeStr);
    static std::pair<int, bool> convert_string_to_int(const std::string& s);
};