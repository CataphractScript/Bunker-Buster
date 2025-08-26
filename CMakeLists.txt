# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and language
project(BunkerBuster LANGUAGES CXX)

# Set the C++ standard (C++17 in this case)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Use standard C++, no compiler-specific extensions

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source files from src/ and main.cpp
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/main.cpp"
)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Optionally, link external libraries here
# target_link_libraries(${PROJECT_NAME} PRIVATE <library_name>)

# Set compiler warnings (recommended for best practices)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
