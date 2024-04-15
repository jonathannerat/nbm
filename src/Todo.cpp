#include "Todo.hpp"

Todo::Todo(size_t id, std::string summary, TodoStatus status)
    : _id(id), _summary(summary), _status(status) {}

size_t Todo::id() const { return _id; }

std::string_view Todo::summary() const { return _summary; }

TodoStatus Todo::status() const { return _status; }

bool Todo::is_pending() const { return _status == TodoStatus::PENDING; }

bool Todo::is_started() const { return _status == TodoStatus::STARTED; }

bool Todo::is_done() const { return _status == TodoStatus::DONE; }

const std::set<std::string> &Todo::tags() const { return _tags; }

void Todo::set_summary(std::string new_summary) { _summary = new_summary; }

bool Todo::tag(std::string tag) {
    auto p = _tags.insert(tag);
    return p.second;
}

bool Todo::untag(std::string tag) { return _tags.erase(tag) > 0; }
