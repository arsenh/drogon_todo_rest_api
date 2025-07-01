#pragma once

#include <functional>

#include "todo.hpp"

#include <vector>
#include <optional>

class IDBRepository {
public:

    virtual void get_todos(
    const std::function<void(const std::vector<TodoEntity>&)>& on_success,
    const std::function<void(const std::string&)>& on_error) = 0;

    virtual void get_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) = 0;

    virtual void create_todo(
        const std::string& title,
        const std::string& description,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) = 0;

    virtual void update_todo_by_id(
        int id,
        const std::optional<std::string>& title,
        const std::optional<std::string>& description,
        const std::optional<bool>& completed,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) = 0;


    virtual void delete_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) = 0;

    virtual ~IDBRepository() = default;
};
