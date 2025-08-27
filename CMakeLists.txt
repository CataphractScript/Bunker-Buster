cmake_minimum_required(VERSION 3.15)

project(BunkerBuster VERSION 1.0 LANGUAGES CXX)

# Use at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

# Source files
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sim/simulator.cpp
    ${CMAKE_SOURCE_DIR}/src/graph/graph.cpp
    ${CMAKE_SOURCE_DIR}/src/data/graph_data.cpp
    ${CMAKE_SOURCE_DIR}/src/data/missile_data.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/missile.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/city.cpp
)

add_executable(BunkerBuster ${SRC_FILES})

# Include directories (project-local headers)
target_include_directories(BunkerBuster PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# If you prefer a different binary name, change the target name above or set this
set_target_properties(BunkerBuster PROPERTIES OUTPUT_NAME "bunker_buster")

# Installation (optional)
install(TARGETS BunkerBuster RUNTIME DESTINATION bin)
