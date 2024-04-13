#include <string>
#include <vector>

#include "todos.hpp"

int main(int argc, char **argv) {
  std::vector<Todo> todos(load_todos());

  if (argc == 1) {
    print_todos(todos);
  } else {
    std::string_view command(argv[1]);

    if (command == "add") {
      Todo new_todo{argv[2], TodoStatus::PENDING};
      todos.emplace_back(new_todo);
    } else {
      size_t idx = static_cast<size_t>(std::stoi(argv[2]));
      if (command == "edit") {
        todos[idx].summary = argv[3];
      } else if (command == "done") {
        todos[idx].status = TodoStatus::DONE;
      } else if (command == "doing") {
        todos[idx].status = TodoStatus::DOING;
      }
    }

    save_todos(todos);
  }
}
