#include "pq_dbrepository.hpp"

void PQDBRepository::get_todos(
    const std::function<void(const std::vector<TodoEntity>&)>& on_success,
    const std::function<void(const std::string&)>& on_error)
{
    const std::string sql = "SELECT * FROM todos;";
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        LOG_ERROR << "DBClient not found!";
        on_error("DBClient not found!");
        return;
    }

    dbClient->execSqlAsync(
        sql,
        [on_success](const drogon::orm::Result &result) {
        std::vector<TodoEntity> todos;
        for (const auto& row : result) {
            TodoEntity todo;
            todo.id = row["id"].as<int>();
            todo.title = row["title"].as<std::string>();
            todo.description = row["description"].isNull()? "" : row["description"].as<std::string>();
            todo.completed = row["completed"].as<bool>();
            todo.created_at = TodoEntity::parse_ISO8601(row["created_at"].as<std::string>());
            todos.push_back(std::move(todo));
        }
        on_success(todos);
    },
    [on_error](const drogon::orm::DrogonDbException &e) {
        LOG_ERROR << "Database error: " << e.base().what();
        on_error(std::string("Database error: ") + e.base().what());
    });
}

void PQDBRepository::get_todo_by_id(
    int id,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error)
{
    const auto sql = "SELECT * FROM todos WHERE id = $1;";
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        LOG_ERROR << "DBClient not found!";
        on_error("DBClient not found!");
        return;
    }

    dbClient->execSqlAsync(
        sql,
        [on_success, on_error](const drogon::orm::Result &result) {
            if (result.empty())
            {
                // id not found
                on_success(std::nullopt);
                return;
            }
            if (result.size() > 1)
            {
                // error case, id in database must be unique
                on_error("uniqueness of identifiers is violated");
            }
            const auto& row = result[0];
            TodoEntity todo;
            todo.id = row["id"].as<int>();
            todo.title = row["title"].as<std::string>();
            todo.description = row["description"].isNull()? "" : row["description"].as<std::string>();
            todo.completed = row["completed"].as<bool>();
            todo.created_at = TodoEntity::parse_ISO8601(row["created_at"].as<std::string>());
            on_success(todo);
        },
    [on_error](const drogon::orm::DrogonDbException &e) {
        LOG_ERROR << "Database error: " << e.base().what();
        on_error(std::string("Database error: ") + e.base().what());
    }, id);
}

void PQDBRepository::create_todo(
    const std::string& title,
    const std::string& description,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error)
{
    const auto sql = "INSERT INTO todos (title, description, completed) VALUES ($1, $2, $3) RETURNING *;";
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        LOG_ERROR << "DBClient not found!";
        on_error("DBClient not found!");
        return;
    }

    dbClient->execSqlAsync(
    sql,
    [on_success](const drogon::orm::Result &result) {
        if (result.empty())
        {
            // insertion failed
            on_success(std::nullopt);
            return;
        }
        // return to client TodoEntitiy that added
        const auto& row = result[0];
        TodoEntity todo;
        todo.id = row["id"].as<int>();
        todo.title = row["title"].as<std::string>();
        todo.description = row["description"].isNull()? "" : row["description"].as<std::string>();
        todo.completed = row["completed"].as<bool>();
        todo.created_at = TodoEntity::parse_ISO8601(row["created_at"].as<std::string>());
        on_success(todo);
    },
[on_error](const drogon::orm::DrogonDbException &e) {
    LOG_ERROR << "Database error: " << e.base().what();
    on_error(std::string("Database error: ") + e.base().what());
    }, title, description, false);
}

void PQDBRepository::update_todo_by_id(
    int id,
    const std::optional<std::string>& title,
    const std::optional<std::string>& description,
    const std::optional<bool>& completed,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error)
{
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        LOG_ERROR << "DBClient not found!";
        on_error("DBClient not found!");
        return;
    }

    get_todo_by_id(
        id,
        [=](const std::optional<TodoEntity>& todo)
        {
            if (!todo)
            {
                on_success(std::nullopt);
                return;
            }

            const TodoEntity& oldTodo = *todo;

            dbClient->execSqlAsync(
                "UPDATE todos SET title = $1, description = $2, completed = $3 WHERE id = $4 RETURNING *;",
                [on_success](const drogon::orm::Result &result) {
                    if (result.empty()) {
                        on_success(std::nullopt);
                        return;
                    }

                    const auto& row = result[0];
                    TodoEntity todo;
                    todo.id = row["id"].as<int>();
                    todo.title = row["title"].as<std::string>();
                    todo.description = row["description"].isNull() ? "" : row["description"].as<std::string>();
                    todo.completed = row["completed"].as<bool>();
                    todo.created_at = TodoEntity::parse_ISO8601(row["created_at"].as<std::string>());
                    on_success(todo);
                },
                [on_error](const drogon::orm::DrogonDbException &e) {
                    LOG_ERROR << "Database error: " << e.base().what();
                    on_error(std::string("Database error: ") + e.base().what());
                },
                title.value_or(oldTodo.title),
                description.value_or(oldTodo.description),
                completed.value_or(oldTodo.completed),
                id
            );
        },
        [on_error](const std::string& err)
        {
            on_error(err);
        }
    );
}

void PQDBRepository::delete_todo_by_id(
    int id,
    const std::function<void(std::optional<TodoEntity>)>& on_success,
    const std::function<void(const std::string&)>& on_error)
{
    const auto sql = "DELETE FROM todos WHERE id = $1 RETURNING *;";
    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)
    {
        LOG_ERROR << "DBClient not found!";
        on_error("DBClient not found!");
        return;
    }

    dbClient->execSqlAsync(
    sql,
    [on_success](const drogon::orm::Result &result) {
        if (result.empty())
        {
            // id not found
            on_success(std::nullopt);
            return;
        }
        const auto& row = result[0];
        TodoEntity todo;
        todo.id = row["id"].as<int>();
        todo.title = row["title"].as<std::string>();
        todo.description = row["description"].isNull()? "" : row["description"].as<std::string>();
        todo.completed = row["completed"].as<bool>();
        todo.created_at = TodoEntity::parse_ISO8601(row["created_at"].as<std::string>());
        on_success(todo);
    },
[on_error](const drogon::orm::DrogonDbException &e) {
    LOG_ERROR << "Database error: " << e.base().what();
    on_error(std::string("Database error: ") + e.base().what());
    }, id);
}