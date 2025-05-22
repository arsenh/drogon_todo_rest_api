#include "../include/mongo_dbrepository.hpp"

MongoDBRepository::MongoDBRepository(const std::string &uri, const std::string &database)
{
    LOG_INFO << "MongoDBRepository constructor";
    LOG_INFO << "URI: " << uri;
    LOG_INFO << "Database: " << database;
    // TODO: connect to MongoDB, and initialize mongo client member
    // TODO: add exception handling for uri and database if empty
}

std::vector<TodoEntity> & MongoDBRepository::get_todos()
{

}

std::optional<TodoEntity> MongoDBRepository::get_todo_by_id(int id)
{

}

TodoEntity MongoDBRepository::create_todo(const std::string &title, const std::string &description)
{

}

std::optional<TodoEntity> MongoDBRepository::update_todo_by_id(int id, const std::optional<std::string> &title,
    const std::optional<std::string> &description, const std::optional<bool> &completed)
{

}

std::optional<TodoEntity> MongoDBRepository::delete_todo_by_id(int id)
{

}
