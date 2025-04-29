# drogon_todo_rest_api
Todo REST API on Drogon Framework

Compile commands:
In application directory.

conan install . --output-folder=build --build=missing -s build_type=Debug
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
