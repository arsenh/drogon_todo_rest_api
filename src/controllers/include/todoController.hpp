#pragma once

#include <drogon/HttpController.h>

#include <string>

using namespace drogon;

class Todo final : public HttpController<Todo>
{
    static constexpr  std::string_view prefix = "/todo";

public:
    METHOD_LIST_BEGIN
    METHOD_ADD(Todo::test_api, "/test", Get, "RequestLogger");
    METHOD_LIST_END

protected:
    void test_api(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

private:
    static std::string getPatternPrefix(std::string pattern);
};