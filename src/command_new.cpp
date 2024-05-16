#include "command_new.hpp"

using Type = Command::Type;

const Command *Command::from(Args args) {
  Type t = resolve_type(args[0]);

  switch (t) {
  case Type::LIST:
    return ListCommand::from(args);
    break;
  }

  return nullptr;
}

using NameToType =
    std::array<std::pair<std::string_view, Type>, static_cast<size_t>(Command::Type::SIZE)>;
NameToType name_to_type({
    {"list", Type::LIST},
    {"edit", Type::ADD},
    {"rm", Type::REMOVE},
    {"tag", Type::TAG},
});

Command::Type Command::resolve_type(const std::string_view &name) {
  std::optional<Type> resolved;

  for (auto &p : name_to_type) {
    if (p.first.starts_with(name)) {
      if (resolved.has_value()) {
        // name matches multiple commands, so we default to "list" command
        resolved.reset();
        break;
      } else {
        resolved = p.second;
      }
    }
  }

  return resolved.value_or(Command::Type::LIST);
}

const ListCommand *ListCommand::from(Args args) {
  Options opts{};

  Args list_args = opts.parse(args).subspan(1); // remove "list" command name

  return nullptr;
}

void ListCommand::execute(TodoManager &tm) {
  tm.list();
}
