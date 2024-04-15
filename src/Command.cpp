#include "Command.hpp"

#include <optional>
#include <stdexcept>

std::map<std::string_view, CommandType> Command::names = {
    {"list", CommandType::LIST},          {"add", CommandType::ADD},
    {"edit", CommandType::EDIT},          {"remove", CommandType::REMOVE},
    {"undo", CommandType::CHANGE_STATUS}, {"start", CommandType::CHANGE_STATUS},
    {"done", CommandType::CHANGE_STATUS}, {"tag", CommandType::TAG},
};

CommandType Command::resolve_type(std::string_view name) {
    for (auto &entry : names) {
        if (entry.first.starts_with(name)) {
            return entry.second;
        }
    }

    throw std::invalid_argument("cannot resolve to command type");
}

const Command *Command::parse(int argc, char **argv) {
    if (argc == 1) {
        return new ListCommand();
    }

    switch (resolve_type(argv[1])) {
    case CommandType::LIST:
        return new ListCommand();
    case CommandType::ADD:
        return AddCommand::parse(argc, argv);
    case CommandType::REMOVE:
        return RemoveCommand::parse(argc, argv);
    case CommandType::EDIT:
        return EditCommand::parse(argc, argv);
    case CommandType::CHANGE_STATUS:
        return ChangeStatusCommand::parse(argc, argv);
    case CommandType::TAG:
        return TagCommand::parse(argc, argv);
    }
}

AddCommand *AddCommand::parse(int argc, char **argv) {
    if (argc < 3) {
        throw std::invalid_argument("not enough arguments to create todo");
    }
    return new AddCommand(argv[2]);
}

RemoveCommand *RemoveCommand::parse(int argc, char **argv) {
    if (argc < 3) {
        throw std::invalid_argument("not enough arguments to remove todo");
    }
    size_t id = std::stoul(argv[2]);
    return new RemoveCommand(id);
}

EditCommand *EditCommand::parse(int argc, char **argv) {
    if (argc < 4) {
        throw std::invalid_argument("not enough arguments to edit todo");
    }
    size_t id = std::stoul(argv[2]);
    return new EditCommand(id, argv[3]);
}

ChangeStatusCommand *ChangeStatusCommand::parse(int argc, char **argv) {
    if (argc < 3) {
        throw std::invalid_argument("not enough arguments to edit todo");
    }
    std::string_view command = argv[1]; // is either 'undo' / 'start' / 'done'
    char c = command[0];
    size_t id = std::stoul(argv[2]);
    TodoStatus status = c == 'u'   ? TodoStatus::PENDING
                        : c == 's' ? TodoStatus::STARTED
                                   : TodoStatus::DONE;

    return new ChangeStatusCommand(id, status);
}

TagCommand *TagCommand::parse(int argc, char **argv) {
    if (argc < 4) {
        throw std::invalid_argument("not enough arguments to tag todo");
    }

    size_t id = std::stoul(argv[2]);
    std::vector<std::string> diff_tags;
    for (size_t i = 3; i < argc; i++) {
        auto t = argv[i];

        if (!(t[0] == '-' || t[0] == '+')) {
            throw std::invalid_argument("invalid tag syntax, should start with -/+");
        }

        diff_tags.push_back(t);
    }

    return new TagCommand(id, diff_tags);
}

void ListCommand::execute(TodoManager &tm) const { tm.list(); }

void AddCommand::execute(TodoManager &tm) const {
    tm.add(summary);
    tm.save();
}

void RemoveCommand::execute(TodoManager &tm) const {
    tm.remove(id);
    tm.save();
}

void EditCommand::execute(TodoManager &tm) const {
    tm.edit(id, summary);
    tm.save();
}

void ChangeStatusCommand::execute(TodoManager &tm) const {
    tm.set_status(id, status);
    tm.save();
}

void TagCommand::execute(TodoManager &tm) const {
    tm.apply_tags(id, diff_tags);
    tm.save();
}
