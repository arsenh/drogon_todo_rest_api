#pragma once

#include "todo.hpp"

#include <vector>
#include <optional>

class TodoService final
{
public:
    TodoService()
    {
        create_dummy_data_for_test();
    }

    std::vector<TodoEntity>& get_todos();
    std::optional<TodoEntity> get_todo_by_id(int id);
    TodoEntity create_todo(int id, const std::string& title, const std::string& description, bool completed);
    std::optional<TodoEntity> update_todo_by_id(int id, const std::optional<std::string>& title, const std::optional<std::string>& description, const std::optional<bool>& completed);
    std::optional<TodoEntity> delete_todo_by_id(int id);

private:
    void create_dummy_data_for_test(); // DELETE: for testing only
private:
    std::vector<TodoEntity> m_todos;
};