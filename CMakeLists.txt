cmake_minimum_required(VERSION 3.10)
project(playground)

set(CMAKE_CXX_STANDARD 17)

add_executable(strong_typedef_examples
        src/namedtype.cpp
        src/strong_type.cpp
        src/type_safe.cpp
        src/stype.cpp
        src/main.cpp)

target_link_libraries(strong_typedef_examples PUBLIC ext_namedtype ext_strong_type ext_type_safe ext_stype)

add_subdirectory(ext)
