cmake_minimum_required(VERSION 3.28)
project(state_machines)

set(CMAKE_CXX_STANDARD 17)

add_executable(state_machines main.cpp
        classic.hpp
        template_id.hpp
        template_states.hpp
        template_events.hpp)
