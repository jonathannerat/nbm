#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define TODOS "todos.txt"

enum class TodoStatus : char { PENDING = ' ', STARTED = 'O', DONE = 'X' };

class Todo {
  public:
    static Todo parse_line(std::string);
    Todo(std::string);

    size_t id() const;
    std::string_view summary() const;
    bool is_pending() const;
    bool is_started() const;
    bool is_done() const;

    void set_summary(std::string);
    void set_pending();
    void set_started();
    void set_done();

    std::string dump() const;

  private:
    Todo(size_t id, std::string summary, TodoStatus status);

    size_t _id;
    std::string _summary;
    TodoStatus _status;
};

std::vector<Todo> load_todos();
void save_todos(const std::vector<Todo> &todos);
void print_todos(const std::vector<Todo> &todos, std::ostream &os = std::cout);
