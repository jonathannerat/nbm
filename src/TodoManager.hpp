#ifndef TODOMANAGER_HPP
#define TODOMANAGER_HPP

#include <string>
#include <vector>

#include "Todo.hpp"

class TodoManager {
  public:
    TodoManager(const std::string &);

    const std::vector<Todo> &todos() const;
    void save() const;
    void list() const;

    void add(std::string);
    void remove(size_t);
    void edit(size_t, std::string);
    void set_status(size_t, TodoStatus);
    void apply_tags(size_t, std::vector<std::string>);

  private:
    std::string serialize(const Todo &) const;
    Todo deserialize(const std::string &s) const;

    std::vector<Todo> _todos;
    std::string _path;
    size_t next_id = 0;
};

#endif // TODOMANAGER_HPP
