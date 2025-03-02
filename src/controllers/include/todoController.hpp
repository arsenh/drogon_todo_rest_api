#pragma once

#include <drogon/HttpController.h>

#include <string>

using namespace drogon;

class Todo final : public HttpController<Todo>
{
public:
    METHOD_LIST_BEGIN
    METHOD_ADD(Todo::get_todos, "/todos", Get, "RequestLogger");
    METHOD_ADD(Todo::get_todo_by_id, "/todos/{id}", Get, "RequestLogger");
    METHOD_ADD(Todo::create_todo, "/todos", Post, "RequestLogger");
    METHOD_ADD(Todo::update_todo_by_id, "/todos/{id}", Patch, "RequestLogger");
    METHOD_ADD(Todo::delete_todo_by_id, "/todos/{id}", Delete, "RequestLogger");

    METHOD_LIST_END

protected:
    //void test_api(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

    void get_todos(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void get_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void create_todo(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void update_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
    void delete_todo_by_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
};