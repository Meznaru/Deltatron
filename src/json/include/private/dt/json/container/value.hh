// json_value.hh

#pragma once

#include <dt/json/container/type.hh>

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace dt {

class json_lexer;

class json_semantic_analysis;

class json_value final {
public:
  using value_t = std::optional<std::variant<std::string, float, int, bool>>;

  friend class ::dt::json_lexer;
  friend class ::dt::json_semantic_analysis;

private:
  json_t       _type;
  std::size_t  _line;
  value_t      _value;

public:
  constexpr auto type() const noexcept -> json_t      { return _type; }
  constexpr auto line() const noexcept -> std::size_t { return _line; }

  template <typename T>
  std::optional<T> opt_val() const noexcept {
    if (T const* v{}; _value && (v = std::get_if<T>(&_value.value())))
      return *v;

    return std::nullopt;
  }

private:
  json_value(json_t type, std::size_t line, value_t value = std::nullopt) noexcept
  : _type(type),
    _line(line),
    _value(value) {}
};

using json_stream_t = std::vector<json_value>;

}
