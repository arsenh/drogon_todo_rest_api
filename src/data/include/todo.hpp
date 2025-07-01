#pragma once

#include <string>
#include <chrono>
#include <json/value.h>
#include <ctime>
#include <iomanip>
#include <sstream>

struct TodoEntity
{
    int id;
    std::string title;
    std::string description;
    bool completed;
    std::chrono::time_point<std::chrono::system_clock> created_at;


    static Json::Value todos_to_json(const std::vector<TodoEntity>& todos);
    static Json::Value todo_to_json(const TodoEntity& todo);
    static std::string time_point_to_ISO8601(const std::chrono::time_point<std::chrono::system_clock>& timePoint);
    static std::chrono::time_point<std::chrono::system_clock> parse_ISO8601(const std::string& timeStr);
    static std::pair<int, bool> convert_string_to_int(const std::string& s);
};


inline Json::Value TodoEntity::todos_to_json(const std::vector<TodoEntity>& todos)
{
    Json::Value jsonArray(Json::arrayValue);

    for (const auto& todo : todos) {
        Json::Value jsonTodo = todo_to_json(todo);
        jsonArray.append(jsonTodo);
    }

    return jsonArray;
}

inline Json::Value TodoEntity::todo_to_json(const TodoEntity &todo)
{
    Json::Value jsonTodo{};
    jsonTodo["id"] = todo.id;
    jsonTodo["title"] = todo.title;
    jsonTodo["description"] = todo.description;
    jsonTodo["completed"] = todo.completed;
    jsonTodo["created_at"] = time_point_to_ISO8601(todo.created_at);
    return jsonTodo;
}

inline std::string TodoEntity::time_point_to_ISO8601(const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
    const std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
    const std::tm tm = *std::gmtime(&timeT);  // Convert to UTC time

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");  // Format as ISO 8601
    return oss.str();
}

inline std::chrono::time_point<std::chrono::system_clock> TodoEntity::parse_ISO8601(const std::string& timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");  // Parse ISO 8601 format
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

inline std::pair<int, bool> TodoEntity::convert_string_to_int(const std::string &s)
{
    try {
        size_t pos;
        if (int value = std::stoi(s, &pos); pos == s.length() && value >= 0) {
            return {value, true};
        }
    } catch (...) {
        // Fall through
    }
    return {0, false}; // Or any default
}
