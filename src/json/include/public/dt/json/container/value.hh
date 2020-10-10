// json_value.hh

#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace dt {

enum class json_value_t {
  Bool, String, Float, Integer, Null,

  Object, Array,

  LBrace = '{', LBrack = '[',
  RBrace = '}', RBrack = ']',
  Comma  = ',', Colon  = ':'
};

class json_lexer;

class json_value final {
public:
  using value_type = std::optional<std::variant<std::string_view, float, long, bool>>;
  using stream_type = std::vector<json_value>;

private:
  friend class ::dt::json_lexer;

  json_value_t _type;
  std::size_t  _line;
  value_type   _value;

public:
  constexpr auto type() const noexcept { return _type; }
  constexpr auto line() const noexcept { return _line; }

  constexpr auto integer_value() const noexcept { return std::get<long>(_value.value());  }
  constexpr auto float_value()   const noexcept { return std::get<float>(_value.value()); }
  constexpr auto bool_value()    const noexcept { return std::get<bool>(_value.value());  }

  std::string string_value() const noexcept {
    auto const view = std::get<std::string_view>(_value.value());
    return std::string(view.data(), view.size());
  }

private:
  json_value(json_value_t type, std::size_t line, value_type value = std::nullopt)
  : _type(type),
    _line(line),
    _value(value) {}
};

}
