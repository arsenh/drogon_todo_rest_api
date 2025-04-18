#include "todo_service.hpp"

#include <algorithm>

std::vector<TodoEntity>& TodoService::get_todos()
{
    return m_todos;
}

std::optional<TodoEntity> TodoService::get_todo_by_id(int id)
{
    const auto it = std::ranges::find_if(m_todos, [id](const TodoEntity& entity)
    {
        return entity.id == id;
    });

    if (it == std::end(m_todos))
    {
        return std::nullopt;
    }
    return *it;
}

TodoEntity TodoService::create_todo(int id, const std::string& title, const std::string& description, bool completed)
{
    //TODO: in the future id parameter will not provided and will generated and store in DB.
    const TodoEntity entity{
        .id = id,
        .title = title,
        .description = description,
        .completed = completed,
        .created_at = std::chrono::system_clock::now()
    };
    m_todos.push_back(entity);
    return entity;
}

std::optional<TodoEntity> TodoService::update_todo_by_id(int id, const std::optional<std::string>& title, const std::optional<std::string>& description, const std::optional<bool>& completed)
{
    const auto it = std::ranges::find_if(m_todos, [id](const TodoEntity& entity)
    {
        return entity.id == id;
    });

    if (it == std::end(m_todos))
    {
        return std::nullopt;
    }

    it->title = title.value_or(it->title);
    it->description = description.value_or(it->description);
    it->completed = completed.value_or(it->completed);
    return *it;
}

std::optional<TodoEntity> TodoService::delete_todo_by_id(int id)
{
    const auto it = std::remove_if(m_todos.begin(), m_todos.end(), [id](const TodoEntity& entity) {
        return entity.id == id;
    });

    if (it == std::end(m_todos))
    {
        return std::nullopt;
    }
    TodoEntity temp = *it;
    m_todos.erase(it, m_todos.end());
    return temp;
}

void TodoService::create_dummy_data_for_test()
{
    m_todos.emplace_back(0, "Note N0", "Description 0", false, std::chrono::system_clock::now());
    m_todos.emplace_back(1, "Note N1", "Description 1", true, std::chrono::system_clock::now());
    m_todos.emplace_back(2, "Note N2", "Description 2", false, std::chrono::system_clock::now());
    m_todos.emplace_back(3, "Note N3", "Description 3", true, std::chrono::system_clock::now());
    m_todos.emplace_back(4, "Note N4", "Description 4", true, std::chrono::system_clock::now());
}
