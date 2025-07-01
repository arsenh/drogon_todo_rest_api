#include "todo_service.hpp"
#include <algorithm>

#include <fmt/format.h>
#include <drogon/drogon.h>


TodoService::TodoService()
    : m_db_repository(std::make_unique<PQDBRepository>())
{

}

void TodoService::get_todos(
    const std::function<void(const std::vector<TodoEntity>&)>& on_success,
    const std::function<void(const std::string&)>& on_error) const
{
    m_db_repository->get_todos(on_success, on_error);
}

void TodoService::get_todo_by_id(
    int id,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error) const
{
    m_db_repository->get_todo_by_id(id, on_success, on_error);
}

void TodoService::create_todo(
    const std::string& title,
    const std::string& description,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error) const
{
    m_db_repository->create_todo(title, description, on_success, on_error);
}

void TodoService::update_todo_by_id(
    int id,
    const std::optional<std::string>& title,
    const std::optional<std::string>& description,
    const std::optional<bool>& completed,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error) const
{
    m_db_repository->update_todo_by_id(id, title, description, completed, on_success, on_error);
}

void TodoService::delete_todo_by_id(
    int id,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error) const
{
    m_db_repository->delete_todo_by_id(id, on_success, on_error);
}