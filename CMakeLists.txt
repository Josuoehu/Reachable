cmake_minimum_required(VERSION 3.29)
project(Reachable)

set(CMAKE_CXX_STANDARD 20)

add_executable(Reachable main.cpp)

find_package(Boost 1.70 REQUIRED COMPONENTS filesystem system)

# Verifica que Boost esté disponible
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(mi_programa main.cpp)
    target_link_libraries(mi_programa ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost no encontrado.")
endif()