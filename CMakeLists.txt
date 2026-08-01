cmake_minimum_required(VERSION 3.16)

project(TinyComputer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tinycomputer
    src/main.cpp
    src/Bus.cpp
    src/IoUnit.cpp
    src/RAM.cpp
    src/Registers.cpp
    src/StorageController.cpp
    src/Cpu.cpp
    src/Alu.cpp
)

target_include_directories(tinycomputer PRIVATE
    lib
    src
)

set_target_properties(tinycomputer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/exe
)