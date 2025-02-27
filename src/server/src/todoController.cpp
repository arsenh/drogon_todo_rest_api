#include "todoController.h"


void TodoController::test_api(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "test_api called";

    Json::Value data;
    data["result"] = "ok";
    data["message"] = "Hello World!";
    auto resp = HttpResponse::newHttpJsonResponse(data);
    callback(resp);
}
