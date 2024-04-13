#include "todos.hpp"

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
