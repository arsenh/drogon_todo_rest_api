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

    void get_todos();
    void get_todo_by_id(int id);
    void create_todo(std::string title, std::optional<std::string> description, std::optional<bool> completed);
    void update_todo_by_id(int id, std::optional<std::string> title, std::optional<std::string> description, std::optional<bool> completed);
    void delete_todo_by_id(int id);

private:
    void create_dummy_data_for_test();
private:
    std::vector<TodoEntity> mTodos;
};