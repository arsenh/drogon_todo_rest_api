#include "todo_service.hpp"


std::vector<TodoEntity>& TodoService::get_todos()
{
    return m_todos;
}

void TodoService::get_todo_by_id(int id)
{

}

void TodoService::create_todo(const std::string& title, const std::optional<std::string>& description, const std::optional<bool>& completed)
{

}

void TodoService::update_todo_by_id(int id, const std::optional<std::string>& title, const std::optional<std::string>& description, const std::optional<bool>& completed)
{

}

void TodoService::delete_todo_by_id(int id)
{

}

void TodoService::create_dummy_data_for_test()
{
    m_todos.emplace_back(0, "Note N0", "Description 0", false, std::chrono::system_clock::now());
    m_todos.emplace_back(1, "Note N1", "Description 1", true, std::chrono::system_clock::now());
    m_todos.emplace_back(2, "Note N2", "Description 2", false, std::chrono::system_clock::now());
    m_todos.emplace_back(3, "Note N3", "Description 3", true, std::chrono::system_clock::now());
    m_todos.emplace_back(4, "Note N4", "Description 4", true, std::chrono::system_clock::now());
}
