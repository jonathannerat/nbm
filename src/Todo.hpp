#ifndef TODO_HPP
#define TODO_HPP

#include <set>
#include <string>

enum class TodoStatus : char {
    PENDING = ' ',
    STARTED = '>',
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
    const std::set<std::string> &tags() const;

    void set_summary(std::string);
    bool tag(std::string);
    bool untag(std::string);

  private:
    friend class TodoManager;
    Todo(size_t id, std::string summary, TodoStatus status);

    size_t _id;
    std::string _summary;
    TodoStatus _status;
    std::set<std::string> _tags;
};

#endif // TODO_HPP
