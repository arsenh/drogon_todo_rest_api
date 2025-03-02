#include "todoController.hpp"

#include <format>

void Todo::get_todos(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("call: {}", "get_todos");
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}

void Todo::get_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
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

