add_executable(app main.cpp)

target_link_libraries(app PRIVATE Catch2::Catch2WithMain server database)

set_target_properties(app PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)