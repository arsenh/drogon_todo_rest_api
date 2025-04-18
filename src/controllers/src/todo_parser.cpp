#include "todo_parser.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>


Json::Value TodoParser::todos_to_json(const std::vector<TodoEntity>& todos)
{
  Json::Value jsonArray(Json::arrayValue);

  for (const auto& todo : todos) {
    Json::Value jsonTodo = todo_to_json(todo);
    jsonArray.append(jsonTodo);
  }

  return jsonArray;
}

Json::Value TodoParser::todo_to_json(const TodoEntity &todo)
{
  Json::Value jsonTodo{};
  jsonTodo["id"] = todo.id;
  jsonTodo["title"] = todo.title;
  jsonTodo["description"] = todo.description;
  jsonTodo["completed"] = todo.completed;
  jsonTodo["created_at"] = time_point_to_ISO8601(todo.created_at);
  return jsonTodo;
}

std::string TodoParser::time_point_to_ISO8601(const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
  const std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
  const std::tm tm = *std::gmtime(&timeT);  // Convert to UTC time

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");  // Format as ISO 8601
  return oss.str();
}

std::chrono::time_point<std::chrono::system_clock> TodoParser::parse_ISO8601(const std::string& timeStr) {
  std::tm tm = {};
  std::istringstream ss(timeStr);
  ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");  // Parse ISO 8601 format
  return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::pair<int, bool> TodoParser::convert_string_to_int(const std::string &s)
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

