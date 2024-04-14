#include "TodoManager.hpp"

#include <exception>
#include <fstream>
#include <functional>
#include <sstream>

TodoManager::TodoManager(const std::string &path) : _path(path) {
    std::ifstream input(_path);
    std::string line;

    while (std::getline(input, line)) {
        Todo t = deserialize(line);

        if (t._id >= next_id) {
            next_id = t._id + 1;
        }

        _todos.push_back(t);
    }
}

const std::vector<Todo> &TodoManager::todos() const { return _todos; }

void TodoManager::save() const {
    std::ofstream output(_path);

    for (auto t : _todos) {
        output << serialize(t) << '\n';
    }
}

void TodoManager::list() const {
    std::cout << "ToDo's:\n";

    for (auto t : _todos) {
        std::cout << t._id << ". [" << static_cast<char>(t._status) << "] " << t._summary << '\n';
    }
}

void TodoManager::add(std::string summary) {
    _todos.push_back(Todo(next_id++, summary, TodoStatus::PENDING));
}

void TodoManager::remove(size_t remove_id) {
    for (auto it = _todos.begin(); it < _todos.end(); it++) {
        if (it->_id == remove_id) {
            _todos.erase(it);
            return;
        }
    }

    throw std::invalid_argument("todo id to remove was not found");
}

void with_todo(std::vector<Todo> &todos, size_t search_id, std::function<void(Todo &)> f) {
    for (auto &t : todos) {
        if (t.id() == search_id) {
            f(t);
            return;
        }
    }

    throw std::invalid_argument("todo id was not found");
}

void TodoManager::edit(size_t id, std::string new_summary) {
    with_todo(_todos, id, [new_summary](Todo &t) { t.set_summary(new_summary); });
}
void TodoManager::set_status(size_t id, TodoStatus status) {
    with_todo(_todos, id, [status](Todo &t) { t._status = status; });
}

std::string TodoManager::serialize(const Todo &todo) const {
    std::stringstream ss;

    ss << todo._id << ',' << static_cast<char>(todo._status) << ',' << todo._summary;

    return ss.str();
}

Todo TodoManager::deserialize(const std::string &s) const {
    size_t first_sep_index = s.find(',');

    size_t id = std::stoi(s.substr(0, first_sep_index));
    TodoStatus status = static_cast<TodoStatus>(s[first_sep_index + 1]);
    std::string summary = s.substr(first_sep_index + 3);

    return Todo(id, summary, status);
}
