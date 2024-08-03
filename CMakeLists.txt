cmake_minimum_required(VERSION 3.28)
project(state_machines)

set(CMAKE_CXX_STANDARD 17)

add_executable(state_machines main.cpp
        simple.hpp
        template_id.hpp
        variadic_flexible.hpp
        variadic_states.hpp
        variadic_simple.hpp
)
