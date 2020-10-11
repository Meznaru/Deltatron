// json_value.hh

#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace dt {

enum class json_value_t {
  Null, Bool, String, Float, Integer,

  Object, Array,

  LBrace = '{', LBrack = '[',
  RBrace = '}', RBrack = ']',
  Comma  = ',', Colon  = ':'
};

class json_lexer;

class json_value final {
public:
  using value_type = std::optional<std::variant<std::string, float, int, bool>>;

private:
  json_value_t _type;
  std::size_t  _line;
  value_type   _value;

  friend class ::dt::json_lexer;

public:
  constexpr auto type() const noexcept { return _type; }
  constexpr auto line() const noexcept { return _line; }

  constexpr auto integer_value() const noexcept { return std::get<int>(_value.value());  }
  constexpr auto float_value()   const noexcept { return std::get<float>(_value.value()); }
  constexpr auto bool_value()    const noexcept { return std::get<bool>(_value.value());  }

  auto string_value() const noexcept { return std::get<std::string>(_value.value()); }

private:
  json_value(json_value_t type, std::size_t line, value_type value = std::nullopt) noexcept
  : _type(type),
    _line(line),
    _value(value) {}
};

using json_stream_t = std::vector<json_value>;

}
