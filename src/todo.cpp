#include "todo.hpp"
#include <sstream>

static size_t global_id = 0;

Todo Todo::parse_line(std::string line) {
    size_t sep_index = line.find(',');
    size_t id = std::stoi(line.substr(0, sep_index));
    TodoStatus status = (TodoStatus)line[sep_index + 1];

    if (id >= global_id) {
        global_id = id + 1;
    }

    return Todo(id, line.substr(sep_index + 3), status);
}

Todo::Todo(size_t id, std::string summary, TodoStatus status)
    : _id(id), _summary(summary), _status(status) {}

Todo::Todo(std::string summary) : Todo(global_id++, summary, TodoStatus::PENDING) {}

size_t Todo::id() const { return _id; }

std::string_view Todo::summary() const { return _summary; }

bool Todo::is_pending() const { return _status == TodoStatus::PENDING; }

bool Todo::is_started() const { return _status == TodoStatus::STARTED; }

bool Todo::is_done() const { return _status == TodoStatus::DONE; }

void Todo::set_summary(std::string new_summary) { _summary = new_summary; }

void Todo::set_pending() { _status = TodoStatus::PENDING; }

void Todo::set_started() { _status = TodoStatus::STARTED; }

void Todo::set_done() { _status = TodoStatus::DONE; }

std::string Todo::dump() const {
    std::stringstream ss;

    ss << _id << ',' << (char)_status << ',' << _summary;

    return ss.str();
}

std::vector<Todo> load_todos() {
    std::vector<Todo> todos;
    std::ifstream f(TODOS);
    std::string line;

    while (std::getline(f, line)) {
        todos.push_back(Todo::parse_line(line));
    }

    return todos;
}

void save_todos(const std::vector<Todo> &todos) {
    std::ofstream f(TODOS);
    print_todos(todos, f);
}

void print_todos(const std::vector<Todo> &todos, std::ostream &os) {
    for (auto &t : todos) {
        os << t.dump() << '\n';
    }
}
