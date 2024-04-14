#ifndef TODO_HPP
#define TODO_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class TodoStatus : char {
    PENDING = '_',
    STARTED = 'O',
    DONE = 'X',
};

class TodoManager;

class Todo {
  public:
    size_t id() const;
    std::string_view summary() const;
    TodoStatus status() const;
    bool is_pending() const;
    bool is_started() const;
    bool is_done() const;

    void set_summary(std::string);

  private:
    friend class TodoManager;
    Todo(size_t id, std::string summary, TodoStatus status);

    size_t _id;
    std::string _summary;
    TodoStatus _status;
};

#endif // TODO_HPP
