#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define TODOS "todos.txt"

enum class TodoStatus { PENDING, DOING, DONE };

struct Todo {
    std::string summary;
    TodoStatus status;
};

std::istream &operator>>(std::istream &is, Todo &t);
std::ostream &operator<<(std::ostream &os, const Todo &t);
std::vector<Todo> load_todos();
void save_todos(const std::vector<Todo> &todos);
void print_todos(const std::vector<Todo> &todos, std::ostream &os = std::cout);
void add_todo(std::vector<Todo> &todos, const std::string &summary);
void remove_todo(std::vector<Todo> &todos, size_t id);
void edit_todo(std::vector<Todo> &todos, size_t id,
               const std::string &new_summary);
void mark_todo_done(std::vector<Todo> &todos, size_t id);
void mark_todo_doing(std::vector<Todo> &todos, size_t id);
