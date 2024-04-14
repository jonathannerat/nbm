#include <algorithm>
#include <string>
#include <vector>

#include "TodoManager.hpp"

#define TODOS "todos.txt"

int main(int argc, char **argv) {
    TodoManager tm(TODOS);

    if (argc == 1) {
        tm.list();
    } else {
        std::string_view command(argv[1]);

        if (command == "add") {
            tm.add(argv[2]);
        } else if (command == "remove") {
            size_t remove_id = std::stoi(argv[2]);
            tm.remove(remove_id);
        } else {
            size_t id = std::stoi(argv[2]);

            if (command == "edit") {
                tm.edit(id, argv[3]);
            } else if (command == "done") {
                tm.mark_done(id);
            } else if (command == "start") {
                tm.mark_started(id);
            } else if (command == "pending") {
                tm.mark_pending(id);
            }
        }

        tm.save();
    }
}
