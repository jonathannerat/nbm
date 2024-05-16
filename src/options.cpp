#include "options.hpp"

#include <format>
#include <iostream>

bool Options::optb(std::string_view name) const {
  if (_options.contains(name)) {
    auto opt_value = _options.at(name);

    if (opt_value.type != Type::BOOL) {
      throw std::invalid_argument(std::format("option '%s' does not contain a bool value", name));
    }

    return opt_value.value.has_value() && std::get<bool>(opt_value.value.value());
  }

  return false;
}

std::optional<std::string_view> Options::opts(std::string_view name) const {
  std::optional<std::string_view> res;

  if (_options.contains(name)) {
    auto opt_value = _options.at(name);

    if (opt_value.type != Type::STRING) {
      throw std::invalid_argument(std::format("option '%s' does not contain a string value", name));
    }

    if (opt_value.value.has_value())
      res = std::get<std::string_view>(opt_value.value.value());
  }

  return res;
}

std::optional<int> Options::opti(std::string_view name) const {
  std::optional<int> res;

  if (_options.contains(name)) {
    auto opt_value = _options.at(name);

    if (opt_value.type != Type::INT) {
      throw std::invalid_argument(
          std::format("option '%s' does not contain an integer value", name));
    }

    if (opt_value.value.has_value())
      res = std::get<int>(opt_value.value.value());
  }

  return res;
}

Args Options::parse(Args args) { return parse(args, std::optional<size_t>()); }

Args Options::parse(Args args, std::optional<size_t> max_args) {
  auto ait = args.begin();

  for (; ait != args.end(); ait++) {
    std::string_view arg(*ait);
    auto maybe_name = long_option(arg);

    if (!maybe_name.has_value()) {
      maybe_name = short_option(arg);
    }

    if (maybe_name.has_value()) {
      auto name = maybe_name.value();
      auto it = _options.find(name);
      auto &opt_value = it->second;

      switch (opt_value.type) {
      case Type::BOOL:
        opt_value.value = !(opt_value.value.has_value() && std::get<bool>(opt_value.value.value()));
        break;

      case Type::INT:
        opt_value.value = std::stoi(*(++ait));
        break;

      case Type::STRING:
        opt_value.value = *(++ait);
        break;
      }
    } else {
      if (max_args.has_value() && _args.size() + 1 > max_args.value())
        break;

      _args.push_back(arg);
    }
  }

  return Args(ait, args.end());
}

std::optional<std::string_view> Options::long_option(const std::string_view &arg) {
  std::optional<std::string_view> opt_name;

  if (arg.size() >= 3 && arg.starts_with("--") && arg[2] != '-') {
    opt_name.emplace(arg.substr(2));
  }

  return opt_name;
}

std::optional<std::string_view> Options::short_option(const std::string_view &arg) {
  std::optional<std::string_view> opt_name;

  if (arg.size() == 2 && arg[0] == '-') {
    opt_name = arg.substr(1);
  }

  return opt_name;
}
