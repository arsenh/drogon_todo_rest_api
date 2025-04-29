add_executable(unit_tests main.cpp sample.cpp)

target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain server)

set_target_properties(unit_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
