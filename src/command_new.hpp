#ifndef COMMAND_NEW_HPP
#define COMMAND_NEW_HPP

#include <array>
#include <cstdint>

#include "TodoManager.hpp"
#include "options.hpp"

class Command {
public:
  static const Command *from(Args);

  enum class Type : uint8_t {
    LIST = 0,
    ADD,
    EDIT,
    REMOVE,
    CHANGE_STATUS,
    TAG,
    SIZE,
  };

protected:
  Command(Type type) : type(type) {}

  virtual void execute(TodoManager &);

  Type type;

private:
  static Type resolve_type(const std::string_view &);
};

class ListCommand : public Command {
public:
  static const ListCommand *from(Args args);

  ListCommand(TodoManager &);
  void execute(TodoManager &);
};

#endif // COMMAND_NEW_HPP
