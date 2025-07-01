#pragma once

#include "idbrepository.hpp"
#include "todo.hpp"

#include <drogon/drogon.h>

#include <string>


class PQDBRepository final : public IDBRepository {

public:

    void get_todos(
    const std::function<void(const std::vector<TodoEntity>&)>& on_success,
    const std::function<void(const std::string&)>& on_error) override;

    void get_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) override;

    void create_todo(
        const std::string& title,
        const std::string& description,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) override;

    void update_todo_by_id(
        int id,
        const std::optional<std::string>& title,
        const std::optional<std::string>& description,
        const std::optional<bool>& completed,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) override;


    void delete_todo_by_id(
        int id,
        const std::function<void(std::optional<TodoEntity>)>& on_success,
        const std::function<void(const std::string&)>& on_error) override;

    ~PQDBRepository() override = default;
};
