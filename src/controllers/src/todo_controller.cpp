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
    const auto [num_id, ok] = TodoParser::convert_string_to_int(id);

    if (!ok)
    {
        callback(invalid_id());
    }

    if (const auto todo = m_todo_service.get_todo_by_id(num_id); todo.has_value())
    {
        const auto resp = HttpResponse::newHttpJsonResponse(TodoParser::todo_to_json(*todo));
        callback(resp);
    } else
    {
        callback(not_found_response(std::format("resource with id = {} not found", id)));
    }
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

HttpResponsePtr Todo::not_found_response(const std::string &message)
{
    Json::Value json;
    json["error"] = message;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(k404NotFound);
    return resp;
}

HttpResponsePtr Todo::invalid_id()
{
    Json::Value json;
    json["error"] = "invalid id provided";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(k404NotFound);
    return resp;
}
