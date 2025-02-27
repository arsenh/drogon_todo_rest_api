#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
class TodoController : public HttpController<TodoController, false>
{
public:
    TodoController()
    {
        LOG_DEBUG << "TodoController initialized";
    }

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TodoController::test_api, "/test", Get);
    METHOD_LIST_END

    void test_api(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
};