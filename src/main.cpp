#include <algorithm>
#include <string>
#include <vector>

#include "Command.hpp"
#include "TodoManager.hpp"

#define TODOS_FILE "todos.txt"

int main(int argc, char **argv) {
    TodoManager tm(TODOS_FILE);
    const Command *cmd = Command::parse(argc, argv);

    cmd->execute(tm);
}
