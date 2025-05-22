#pragma once

#include "idbrepository.hpp"
#include "../../data/include/todo.hpp"

#include <drogon/drogon.h>

#include <string>


class MongoDBRepository final : public IDBRepository {
public:
    MongoDBRepository(const std::string& uri, const std::string& database);

public:
    std::vector<TodoEntity>& get_todos() override;

    std::optional<TodoEntity> get_todo_by_id(int id) override;

    TodoEntity create_todo(const std::string& title, const std::string& description) override;

    std::optional<TodoEntity> update_todo_by_id(int id, const std::optional<std::string>& title,
        const std::optional<std::string>& description, const std::optional<bool>& completed) override;

    std::optional<TodoEntity> delete_todo_by_id(int id) override;

    ~MongoDBRepository() override = default;
};
