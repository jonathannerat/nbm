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
