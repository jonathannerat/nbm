#include "TodoManager.hpp"

#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>

#include "utils.hpp"

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
    for (auto &t : _todos) {
        std::cout << t._id << ". [" << static_cast<char>(t._status) << "] " << t._summary;

        auto tags = t.tags();
        if (!tags.empty()) {
            std::cout << " (" << join(tags.begin(), tags.end(), ' ') << ')';
        }
        std::cout << '\n';
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

void TodoManager::apply_tags(size_t id, std::vector<std::string> diff_tags) {
    with_todo(_todos, id, [diff_tags](Todo &todo) {
        for (auto &t : diff_tags) {
            if (t[0] == '+') {
                todo.tag(t.substr(1));
            } else {
                todo.untag(t.substr(1));
            }
        }
    });
}

std::string TodoManager::serialize(const Todo &todo) const {
    std::stringstream ss;

    ss << todo._id << ',' << static_cast<char>(todo._status) << ',' << todo._summary << ',';

    auto tags = todo.tags();
    for (auto it = tags.begin(); it != tags.end(); it++) {
        if (it != tags.begin())
            ss << '.';

        ss << *it;
    }

    return ss.str();
}

Todo TodoManager::deserialize(const std::string &s) const {
    auto cols = split(s, ',');

    size_t id = std::stoul(cols[0]);
    TodoStatus status = static_cast<TodoStatus>(cols[1][0]);
    std::string summary = cols[2];
    Todo todo = Todo(id, summary, status);

    for (auto &t : split(cols[3], '.'))
        todo.tag(t);

    return todo;
}
