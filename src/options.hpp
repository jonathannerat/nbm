#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <cstdint>
#include <map>
#include <optional>
#include <span>
#include <string_view>
#include <variant>
#include <vector>

using Args = std::span<const char *>;

class Options {
public:
  enum class Type : uint8_t {
    BOOL,
    INT,
    STRING,
  };

private:
  using Value = std::variant<std::string_view, int, bool>;
  struct OptionValue {
    Type type;
    std::optional<Value> value;
  };

public:
  Options(std::initializer_list<std::pair<std::string_view, OptionValue>> options)
      : _options(options.begin(), options.end()) {}

  const auto opt(std::string_view name) const {
    return _options.contains(name) ? _options.at(name).value : Value();
  }

  bool optb(std::string_view) const;
  std::optional<std::string_view> opts(std::string_view) const;
  std::optional<int> opti(std::string_view) const;
  const std::vector<std::string_view> &args() const { return _args; }

  Args parse(Args);
  Args parse(Args, std::optional<size_t>);
  void print();

private:
  std::optional<std::string_view> long_option(const std::string_view &);
  std::optional<std::string_view> short_option(const std::string_view &);
  std::map<std::string_view, OptionValue> _options;
  std::vector<std::string_view> _args;
};

#endif // OPTIONS_HPP
