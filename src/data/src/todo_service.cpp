#include "todo_service.hpp"


void TodoService::create_dummy_data_for_test()
{
    m_todos.emplace_back(0, "Note N0", "Description 0", false, std::chrono::system_clock::now());
    m_todos.emplace_back(1, "Note N1", "Description 1", true, std::chrono::system_clock::now());
    m_todos.emplace_back(2, "Note N2", "Description 2", false, std::chrono::system_clock::now());
    m_todos.emplace_back(3, "Note N3", "Description 3", true, std::chrono::system_clock::now());
    m_todos.emplace_back(4, "Note N4", "Description 4", true, std::chrono::system_clock::now());
}
