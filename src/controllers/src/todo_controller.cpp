#include "todo_controller.hpp"

#include <format>
#include <set>

#include "todo_parser.hpp"

void Todo::get_todos(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback)
{
    const auto& todos = m_todo_service.get_todos();
    const auto& json_data = TodoParser::todos_to_json(todos);
    const auto resp = HttpResponse::newHttpJsonResponse(json_data);
    callback(resp);
}

void Todo::get_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback, const std::string& id)
{
    const auto [num_id, ok] = TodoParser::convert_string_to_int(id);
    if (!ok)
    {
        callback(not_found_response("invalid id provided"));
        return;
    }

    if (const auto todo = m_todo_service.get_todo_by_id(num_id); todo.has_value())
    {
        const auto resp = HttpResponse::newHttpJsonResponse(TodoParser::todo_to_json(*todo));
        callback(resp);
        return;
    }
    else
    {
        callback(not_found_response(std::format("resource with id = {} not found", id)));
        return;
    }
}

void Todo::create_todo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback)
{
    const auto json = req->getJsonObject();
    if (!json || !check_json_data_fields_name(*json))
    {
        callback(bad_request("Invalid or incorrect json data"));
        return;
    }

    const auto& title = (*json)["title"].asString();
    if (title.empty())
    {
        callback(bad_request("Invalid or incorrect title"));
        return;
    }

    const auto& description = (*json)["description"].asString();

    const auto& todo_entity = m_todo_service.create_todo(title, description);

    const auto resp = drogon::HttpResponse::newHttpJsonResponse(TodoParser::todo_to_json(todo_entity));
    resp->setStatusCode(drogon::k201Created);
    callback(resp);
}

void Todo::update_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, const std::string& id)
{
    const auto [num_id, ok] = TodoParser::convert_string_to_int(id);
    if (!ok)
    {
        callback(not_found_response("invalid id provided"));
        return;
    }

    const auto json = req->getJsonObject();

    if (!json || !check_json_data_fields_name(*json))
    {
        callback(bad_request("Invalid or incorrect json data"));
        return;
    }

    std::optional<std::string> title;
    std::optional<std::string> description;
    std::optional<bool> completed;

    if (json->isMember("title"))
    {
        title = (*json)["title"].asString();
        if (title->empty())
        {
            callback(bad_request("Invalid or incorrect title"));
            return;
        }
    }
    if (json->isMember("description"))
    {
        description = (*json)["description"].asString();
    }
    if (json->isMember("completed"))
    {
        completed = (*json)["completed"].asBool();
    }

    const auto todo_entity = m_todo_service.update_todo_by_id(num_id, title, description, completed);
    if (!todo_entity.has_value())
    {
        callback(not_found_response(std::format("resource with id = {} not found", id)));
        return;
    }

    const auto resp = drogon::HttpResponse::newHttpJsonResponse(TodoParser::todo_to_json(*todo_entity));
    resp->setStatusCode(drogon::k200OK);
    callback(resp);
}

void Todo::delete_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback, const std::string& id)
{
    const auto [num_id, ok] = TodoParser::convert_string_to_int(id);
    if (!ok)
    {
        callback(not_found_response("invalid id provided"));
        return;
    }

    const auto todo_entity = m_todo_service.delete_todo_by_id(num_id);
    if (!todo_entity.has_value())
    {
        callback(not_found_response(std::format("resource with id = {} not found", id)));
        return;
    }

    const auto resp = drogon::HttpResponse::newHttpJsonResponse(TodoParser::todo_to_json(*todo_entity));
    resp->setStatusCode(drogon::k200OK);
    callback(resp);
}

HttpResponsePtr Todo::not_found_response(const std::string& message)
{
    return create_json_response(message, k404NotFound);
}

HttpResponsePtr Todo::bad_request(const std::string& message)
{
    return create_json_response(message, k400BadRequest);
}

HttpResponsePtr Todo::create_json_response(const std::string& message, const HttpStatusCode code)
{
    Json::Value json;
    json["error"] = message;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(code);
    return resp;
}

bool Todo::check_json_data_fields_name(const Json::Value& json)
{
    const std::set<std::string> allowedFields = {"title", "description", "completed"};

    return std::ranges::all_of(json.getMemberNames(), [&allowedFields](const auto& member)
    {
        return allowedFields.contains(member);
    });
}
