#pragma once

#include "todo.hpp"
#include "idbrepository.hpp"
#include "pq_dbrepository.hpp"

#include <vector>
#include <optional>
#include <memory>

struct TodoServiceError
{
    std::string message;
};

class TodoService final
{
public:
    TodoService();

    static void get_todos(
        const std::function<void(const std::vector<TodoEntity>&)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);

    static void get_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);

    static void create_todo(
        const std::string& title,
        const std::string& description,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);

    static void update_todo_by_id(
        int id,
        const std::optional<std::string>& title,
        const std::optional<std::string>& description,
        const std::optional<bool>& completed,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);


    static void delete_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);

private:
    std::unique_ptr<IDBRepository> m_db_repository;
};