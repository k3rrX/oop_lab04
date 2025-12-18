cmake_minimum_required(VERSION 3.10)
project(LAba44)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LABA44
    main.cpp
)

if(MSVC)
    target_compile_options(LABA44 PRIVATE /W4)
else()
    target_compile_options(LABA44 PRIVATE -Wall -Wextra -pedantic)
endif()