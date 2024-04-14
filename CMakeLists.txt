cmake_minimum_required(VERSION 3.10)

project(NotebookManager)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(nbm src/main.cpp src/Todo.cpp src/TodoManager.cpp src/Command.cpp)
