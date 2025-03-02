#include "todoController.hpp"

#include <format>

void Todo::test_api(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    static int counter = 0;
    //LOG_DEBUG << "test_api called" << counter;

    Json::Value data;
    data["result"] = "ok";
    data["message"] = std::format("Hello World! {}", counter);
    auto resp = HttpResponse::newHttpJsonResponse(data);
    ++counter;
    callback(resp);
}

std::string Todo::getPatternPrefix(std::string pattern)
{
    return std::format("{}{}", prefix, pattern);
}

