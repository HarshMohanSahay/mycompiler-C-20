cmake_minimum_required(VERSION 3.10)
project(MyCompiler)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Compiler.cpp
    src/VM.cpp
    src/Bytecode.cpp
)

# Create executable
add_executable(MyCompiler ${SOURCES})

# Include directories
target_include_directories(MyCompiler PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Optional: Enable compiler warnings
if(MSVC)
    target_compile_options(MyCompiler PRIVATE /W4)
else()
    target_compile_options(MyCompiler PRIVATE -Wall -Wextra -Wpedantic)
endif()
