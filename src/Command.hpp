#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <cstdint>
#include <map>

#include "TodoManager.hpp"

enum CommandType : uint8_t {
    LIST = 0,
    ADD,
    EDIT,
    REMOVE,
    CHANGE_STATUS,
    TAG,
};

class Command {
  public:
    static const Command *parse(int, char **);

    virtual void execute(TodoManager &) const = 0;

  protected:
    Command(CommandType type) : type(type) {}
    CommandType type;

  private:
    static CommandType resolve_type(std::string_view);
    static std::map<std::string_view, CommandType> names;
};

class ListCommand : public Command {
  public:
    ListCommand() : Command(CommandType::LIST) {}
    void execute(TodoManager &) const;
};

class AddCommand : public Command {
  public:
    static AddCommand *parse(int, char **);
    void execute(TodoManager &) const;

  private:
    AddCommand(std::string summary) : Command(CommandType::ADD), summary(summary){};
    std::string summary;
};

class EditCommand : public Command {
  public:
    static EditCommand *parse(int, char **);
    void execute(TodoManager &) const;

  private:
    EditCommand(size_t id, std::string summary)
        : Command(CommandType::EDIT), id(id), summary(summary) {}
    size_t id;
    std::string summary;
};

class RemoveCommand : public Command {
  public:
    static RemoveCommand *parse(int, char **);
    void execute(TodoManager &) const;

  private:
    RemoveCommand(size_t id) : Command(CommandType::REMOVE), id(id) {}
    size_t id;
};

class ChangeStatusCommand : public Command {
  public:
    static ChangeStatusCommand *parse(int, char **);
    void execute(TodoManager &) const;

  private:
    ChangeStatusCommand(size_t id, TodoStatus status)
        : Command(CommandType::CHANGE_STATUS), id(id), status(status) {}
    size_t id;
    TodoStatus status;
};

class TagCommand : public Command {
  public:
    static TagCommand *parse(int, char **);
    void execute(TodoManager &) const;

  private:
    TagCommand(size_t id, std::vector<std::string> diff_tags)
        : Command(CommandType::TAG), id(id), diff_tags(diff_tags) {}
    size_t id;
    std::vector<std::string> diff_tags;
};

#endif // COMMAND_HPP
