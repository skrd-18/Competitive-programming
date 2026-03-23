cmake_minimum_required(VERSION 3.10)
project(CS2040C_Lab)

# 1. ESSENTIAL FOR NEOVIM/CLANGD
# This generates compile_commands.json so clangd knows your include paths
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. SET C++ STANDARD
# CS2040C uses modern C++ (C++17 or C++20 is recommended for smart pointers)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. COMPILER FLAGS (Strictness helps with debugging)
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -g)
endif()

# 4. DEFINE YOUR EXECUTABLE
# Replace 'main.cpp' with your actual filename (e.g., 'RGB.cpp' for Lab 0)
add_executable(main leetcode/0445/main.cpp)

# 5. UNIT TESTING (Optional but common in CS2040C)
# If your lab includes a separate test file (e.g., RGB_test.cpp)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp")
  add_executable(run_tests tests.cpp)
endif()

