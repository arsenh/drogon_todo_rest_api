#pragma once

#include "todo.hpp"
#include "idbrepository.hpp"
#include "pq_dbrepository.hpp"

#include <vector>
#include <optional>
#include <memory>

class TodoService final
{
public:
    TodoService();

    void get_todos(
        const std::function<void(const std::vector<TodoEntity>&)>& on_success,
        const std::function<void(const std::string&)>& on_error) const;

    void get_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) const;

    void create_todo(
        const std::string& title,
        const std::string& description,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) const;

    void update_todo_by_id(
        int id,
        const std::optional<std::string>& title,
        const std::optional<std::string>& description,
        const std::optional<bool>& completed,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) const;


    void delete_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) const;

private:
    std::unique_ptr<IDBRepository> m_db_repository;
};