#include "todo_controller.hpp"

#include <fmt/format.h>
#include <set>

void Todo::get_todos(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback)
{
    m_todo_service.get_todos(
    [callback](const std::vector<TodoEntity>& todos) {
        const auto resp = HttpResponse::newHttpJsonResponse(TodoEntity::todos_to_json(todos));
        callback(resp);
    },
    [callback](const std::string& err) {
        callback(internal_server_error("Internal server error: " + err));
    });
}

void Todo::get_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback, const std::string& id)
{
    const auto [num_id, ok] = TodoEntity::convert_string_to_int(id);
    if (!ok)
    {
        callback(not_found_response("invalid id provided"));
        return;
    }

    m_todo_service.get_todo_by_id(num_id,
    [callback, num_id](const std::optional<TodoEntity>& todo) {
        if (!todo)
        {
            callback(not_found_response(fmt::format("resource with id = {} not found", num_id)));
            return;
        }
        const auto resp = HttpResponse::newHttpJsonResponse(TodoEntity::todo_to_json(*todo));
        resp->setStatusCode(drogon::k200OK);
        callback(resp);
    },
    [callback](const std::string& err) {
        callback(internal_server_error(err));
    });
}

void Todo::create_todo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback)
{
    const auto json = req->getJsonObject();
    if (!json || !check_json_data_fields_name(*json))
    {
        callback(bad_request("Invalid or incorrect json data"));
        return;
    }

    try
    {
        const auto& title = (*json)["title"].asString();
        if (title.empty())
        {
            callback(bad_request("Invalid or incorrect title"));
            return;
        }

        const auto& description = (*json)["description"].asString();


        m_todo_service.create_todo(title, description,
        [callback](const std::optional<TodoEntity>& todo) {
            if (!todo)
            {
                callback(internal_server_error("entity insertion failed"));
                return;
            }
                const auto resp = HttpResponse::newHttpJsonResponse(TodoEntity::todo_to_json(*todo));
                resp->setStatusCode(drogon::k201Created);
                callback(resp);
            },
        [callback](const std::string& err) {
            callback(internal_server_error(err));
        });
    }
    catch (const std::exception& e)
    {
        callback(bad_request("Invalid or incorrect json data"));
        return;
    }
}

void Todo::update_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, const std::string& id)
{
    const auto [num_id, ok] = TodoEntity::convert_string_to_int(id);
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

    try
    {
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
            if ((*json)["completed"].type() != Json::booleanValue)
            {
                callback(bad_request("Invalid or incorrect json data"));
                return;
            }
            completed = (*json)["completed"].asBool();
        }
    }
    catch (const std::exception& e)
    {
        callback(bad_request("Invalid or incorrect json data"));
        return;
    }

    m_todo_service.update_todo_by_id(num_id, title, description, completed,
[callback, num_id](const std::optional<TodoEntity>& todo) {
        if (!todo)
        {
            callback(not_found_response(fmt::format("resource with id = {} not found", num_id)));
            return;
        }
            const auto resp = HttpResponse::newHttpJsonResponse(TodoEntity::todo_to_json(*todo));
            resp->setStatusCode(drogon::k200OK);
            callback(resp);
        },
[callback](const std::string& err) {
        callback(internal_server_error(err));
    });
}

void Todo::delete_todo_by_id(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&& callback, const std::string& id)
{
    const auto [num_id, ok] = TodoEntity::convert_string_to_int(id);
    if (!ok)
    {
        callback(not_found_response("invalid id provided"));
        return;
    }

    m_todo_service.delete_todo_by_id(num_id,
[callback, num_id](const std::optional<TodoEntity>& todo) {
        if (!todo)
        {
            callback(not_found_response(fmt::format("resource with id = {} not found", num_id)));
            return;
        }
            const auto resp = HttpResponse::newHttpJsonResponse(TodoEntity::todo_to_json(*todo));
            resp->setStatusCode(drogon::k200OK);
            callback(resp);
        },
[callback](const std::string& err) {
        callback(internal_server_error(err));
    });
}

HttpResponsePtr Todo::not_found_response(const std::string& message)
{
    return create_json_response(message, k404NotFound);
}

HttpResponsePtr Todo::bad_request(const std::string& message)
{
    return create_json_response(message, k400BadRequest);
}

HttpResponsePtr Todo::internal_server_error(const std::string& message)
{
    return create_json_response(message, k500InternalServerError);
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
