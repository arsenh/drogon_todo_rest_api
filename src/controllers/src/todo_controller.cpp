#include "todo_controller.hpp"

#include <format>

#include "todo_parser.hpp"

void Todo::get_todos(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    const auto& todos = m_todo_service.get_todos();
    const auto& json_data = TodoParser::todos_to_json(todos);
    const auto resp = HttpResponse::newHttpJsonResponse(json_data);
    callback(resp);
}

void Todo::get_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string& id)
{
    LOG_DEBUG << "get_todo_by_id, id = " << id << "\n";
    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("call: {}", "get_todo_by_id");
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}

void Todo::create_todo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("call: {}", "create_todo");
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}

void Todo::update_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("call: {}", "update_todo_by_id");
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}

void Todo::delete_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("call: {}", "delete_todo_by_id");
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}

