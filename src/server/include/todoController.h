#pragma once

#include <drogon/HttpController.h>

#include <string>

using namespace drogon;
class TodoController : public HttpController<TodoController, false>
{
    static constexpr  std::string_view prefix = "/todo";
public:
    TodoController()
    {
        LOG_DEBUG << "TodoController initialized";
    }

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TodoController::test_api, getPatternPrefix("/test"), Get);
    METHOD_LIST_END

    void test_api(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

private:
    static std::string getPatternPrefix(std::string pattern);
};