#include <string>
#include <vector>

#include "todo.hpp"

int main(int argc, char **argv) {
    std::vector<Todo> todos(load_todos());

    if (argc == 1) {
        print_todos(todos);
    } else {
        std::string_view command(argv[1]);

        if (command == "add") {
            add_todo(todos, argv[2]);
        } else {
            size_t id = static_cast<size_t>(std::stoi(argv[2]));
            Todo &t = todos[id];

            if (command == "remove") {
                remove_todo(todos, id);
            } else if (command == "edit") {
                edit_todo(todos, id, argv[3]);
            } else if (command == "done") {
                mark_todo_done(todos, id);
            } else if (command == "doing") {
                mark_todo_doing(todos, id);
            }
        }

        save_todos(todos);
    }
}
