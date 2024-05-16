#include <iostream>
#include <span>

#include "TodoManager.hpp"
#include "command_new.hpp"

#define TODOS_FILE "todos.txt"

int main(int argc, const char **argv) {
  Args args(argv, argv + argc);
  TodoManager tm(TODOS_FILE);
  auto cmd = Command::from(args);
}
