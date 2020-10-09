// token.hh

#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace dt {

enum token_id : char {
  Integer, Float, String, Bool, Null,
  LBrace = '{', RBrace = '}',
  LBrack = '[', RBrack = ']',
  Colon  = ':', Comma  = ','
};

class token final {
public:
  using value_type = std::optional<std::variant<std::string_view, int, float, bool>>;

private:
  token_id    const _type;
  std::size_t const _line;
  value_type  const _optval;

public:
  token(token_id const type, std::size_t const line, value_type const opt_value = std::nullopt) noexcept
  : _type(type),
    _line(line),
    _optval(opt_value) {}

  constexpr auto type() const noexcept { return _type; }
  constexpr auto line() const noexcept { return _line; }

  constexpr auto int_value()    const noexcept { return std::get<int             >(_optval.value()); }
  constexpr auto float_value()  const noexcept { return std::get<float           >(_optval.value()); }
  constexpr auto string_value() const noexcept { return std::get<std::string_view>(_optval.value()); }
  constexpr auto bool_value()   const noexcept { return std::get<bool            >(_optval.value()); }

  static constexpr auto token_to_char(token_id const t) noexcept { return static_cast<char    >(t); }
  static constexpr auto char_to_token(char const c)     noexcept { return static_cast<token_id>(c); }
};

std::string token_id_to_string(token const& tok) noexcept {
  auto const t = tok.type();
  switch(t) {
  case token_id::LBrace: [[fallthrough]];
  case token_id::RBrace: [[fallthrough]];
  case token_id::LBrack: [[fallthrough]];
  case token_id::RBrack: [[fallthrough]];
  case token_id::Colon:  [[fallthrough]];
  case token_id::Comma:
    return std::string{token::token_to_char(t)};
  case token_id::Integer:
    return std::to_string(tok.int_value());
  case token_id::Float:
    return std::to_string(tok.float_value());
  case token_id::String:
    return {tok.string_value().begin(), tok.string_value().end()};
  case token_id::Bool:
    return std::to_string(tok.bool_value());
  case token_id::Null:
    return "null";
  }
}


using token_stream_t = std::vector<token>;

}
