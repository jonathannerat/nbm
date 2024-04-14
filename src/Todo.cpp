#include "Todo.hpp"
#include <sstream>

Todo::Todo(size_t id, std::string summary, TodoStatus status)
    : _id(id), _summary(summary), _status(status) {}

size_t Todo::id() const { return _id; }

std::string_view Todo::summary() const { return _summary; }

TodoStatus Todo::status() const { return _status; }

bool Todo::is_pending() const { return _status == TodoStatus::PENDING; }

bool Todo::is_started() const { return _status == TodoStatus::STARTED; }

bool Todo::is_done() const { return _status == TodoStatus::DONE; }

void Todo::set_summary(std::string new_summary) { _summary = new_summary; }
