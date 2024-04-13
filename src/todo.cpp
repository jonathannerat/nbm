#include "todo.hpp"

std::istream &operator>>(std::istream &is, Todo &t) {
    char c;

    is.get(c);

    t.status = (c == ' '   ? TodoStatus::PENDING
                : c == 'O' ? TodoStatus::DOING
                           : TodoStatus::DONE);

    is >> c;

    std::getline(is, t.summary);

    return is;
}

std::ostream &operator<<(std::ostream &os, const Todo &t) {
    os << (t.status == TodoStatus::PENDING ? ' '
           : t.status == TodoStatus::DOING ? 'O'
                                           : 'X');

    os << ',' << t.summary << '\n';

    return os;
}

std::vector<Todo> load_todos() {
    std::vector<Todo> todos;
    std::ifstream f(TODOS);
    Todo t;

    while (f >> t) {
        todos.push_back(t);
    }

    return todos;
}

void save_todos(const std::vector<Todo> &todos) {
    std::ofstream f(TODOS);
    print_todos(todos, f);
}

void print_todos(const std::vector<Todo> &todos, std::ostream &os) {
    for (auto &t : todos) {
        os << t;
    }
}

void add_todo(std::vector<Todo> &todos, const std::string &summary) {
    Todo new_todo{summary, TodoStatus::PENDING};
    todos.emplace_back(new_todo);
}

void remove_todo(std::vector<Todo> &todos, size_t id) {
    size_t i = 0;

    for (auto it = todos.begin(); it != todos.end(); it++, i++) {
        if (i == id) {
            todos.erase(it);
            break;
        }
    }
}

void edit_todo(std::vector<Todo> &todos, size_t id,
               const std::string &new_summary) {
    todos[id].summary = new_summary;
}

void mark_todo_done(std::vector<Todo> &todos, size_t id) {
    todos[id].status = TodoStatus::DONE;
}

void mark_todo_doing(std::vector<Todo> &todos, size_t id) {
    todos[id].status = TodoStatus::DOING;
}
