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

    void get_todos(const std::function<void(const std::vector<TodoEntity>&)>& on_success,
        const std::function<void(const TodoServiceError&)>& on_error);
    std::optional<TodoEntity> get_todo_by_id(int id);
    TodoEntity create_todo(const std::string& title, const std::string& description);
    std::optional<TodoEntity> update_todo_by_id(int id, const std::optional<std::string>& title, const std::optional<std::string>& description, const std::optional<bool>& completed);
    std::optional<TodoEntity> delete_todo_by_id(int id);

private:
    std::unique_ptr<IDBRepository> m_db_repository;
    void create_dummy_data_for_test(); // DELETE: for testing only
    std::vector<TodoEntity> m_todos;
};