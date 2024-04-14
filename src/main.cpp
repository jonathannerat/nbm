#include <algorithm>
#include <string>
#include <vector>

#include "todo.hpp"

int main(int argc, char **argv) {
    std::vector<Todo> todos = load_todos();

    if (argc == 1) {
        print_todos(todos);
    } else {
        std::string_view command(argv[1]);

        if (command == "add") {
            todos.emplace_back(Todo(argv[2]));
        } else {
            size_t id = static_cast<size_t>(std::stoi(argv[2]));
            auto it = std::find_if(todos.begin(), todos.end(),
                                   [id](const Todo &t) { return t.id() == id; });

            if (it == todos.end()) {
                std::cerr << "Couldn't find todo for id: " << id << std::endl;
                exit(EXIT_FAILURE);
            }

            if (command == "remove") {
                todos.erase(it);
            } else if (command == "edit") {
                it->set_summary(argv[3]);
            } else if (command == "done") {
                it->set_done();
            } else if (command == "start") {
                it->set_started();
            }
        }

        save_todos(todos);
    }
}
