#include "todo_parser.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


Json::Value TodoParser::todos_to_json(const std::vector<TodoEntity>& todos)
{
  Json::Value jsonArray(Json::arrayValue);

  for (const auto&[id, title, description,
      completed, created_at] : todos) {

    Json::Value jsonTodo{};

    jsonTodo["id"] = id;
    jsonTodo["title"] = title;
    jsonTodo["description"] = description;
    jsonTodo["completed"] = completed;
    jsonTodo["created_at"] = time_point_to_ISO8601(created_at);
    jsonArray.append(jsonTodo);
  }

  return jsonArray;
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

