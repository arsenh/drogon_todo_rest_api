#pragma once

#include "todo_service.hpp"

#include <drogon/HttpController.h>

#include <string>

using namespace drogon;

class Todo final : public HttpController<Todo>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Todo::get_todos, "/todos", Get, "RequestLogger");
    ADD_METHOD_TO(Todo::get_todo_by_id, "/todos/{id}", Get, "RequestLogger");
    ADD_METHOD_TO(Todo::create_todo, "/todos", Post, "RequestLogger");
    ADD_METHOD_TO(Todo::update_todo_by_id, "/todos/{id}", Patch, "RequestLogger");
    ADD_METHOD_TO(Todo::delete_todo_by_id, "/todos/{id}", Delete, "RequestLogger");
    METHOD_LIST_END

private:
    void get_todos(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void get_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, const std::string&);
    void create_todo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void update_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void delete_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

private:
    TodoService m_todo_service{};
};