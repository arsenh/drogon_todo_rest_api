#pragma once

#include "../../data/include/todo.hpp"

class IDBRepository {
public:
    virtual std::vector<TodoEntity>& get_todos() = 0;

    virtual std::optional<TodoEntity> get_todo_by_id(int id) = 0;

    virtual TodoEntity create_todo(const std::string& title, const std::string& description) = 0;

    virtual std::optional<TodoEntity> update_todo_by_id(int id, const std::optional<std::string>& title, const std::optional<std::string>& description, const std::optional<bool>& completed) = 0;

    virtual std::optional<TodoEntity> delete_todo_by_id(int id) = 0;

    virtual ~IDBRepository() = default;
};
