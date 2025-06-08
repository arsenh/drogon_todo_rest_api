#include "pq_dbrepository.hpp"

#include <pqxx/pqxx>

std::vector<TodoEntity>& PQDBRepository::get_todos()
{
    exit(1);
}

std::optional<TodoEntity> PQDBRepository::get_todo_by_id(int id)
{
    exit(1);
}

TodoEntity PQDBRepository::create_todo(const std::string &title, const std::string &description)
{
    exit(1);
}

std::optional<TodoEntity> PQDBRepository::update_todo_by_id(int id, const std::optional<std::string> &title,
    const std::optional<std::string> &description, const std::optional<bool> &completed)
{
    exit(1);
}

std::optional<TodoEntity> PQDBRepository::delete_todo_by_id(int id)
{
    exit(1);
}
