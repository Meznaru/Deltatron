// json_lexer.hh

#pragma once

#include <dt/json/container/value.hh>

#include <charconv>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace dt {

class lexer_pos final {
  char const* _end;
  char const* _read_head;

public:
  constexpr lexer_pos(char const* read_head, char const* end) noexcept
  : _end(end),
    _read_head(read_head) {}

  constexpr lexer_pos(lexer_pos const& lp) noexcept
  : _end(lp._end),
    _read_head(lp._read_head) {}

  constexpr auto eof()       const noexcept -> bool        { return _read_head == _end; }
  constexpr auto operator*() const noexcept -> char        { return *_read_head;        }
  constexpr auto operator&() const noexcept -> char const* { return _read_head;         }

  constexpr bool operator++() noexcept
  { return _read_head != _end ? static_cast<bool>(++_read_head) : false; }

  constexpr void operator=(char const* p) noexcept
  { _read_head = p; }

  constexpr std::size_t distance() const noexcept
  { return static_cast<std::size_t>(_end - _read_head); }

  constexpr bool operator+=(std::size_t n) noexcept
  { return static_cast<bool>(_read_head += n); }
};

class json_lexer final {
  std::string const& _id;
  std::size_t        _current_line;
  lexer_pos          _pos;

public:
  constexpr json_lexer(std::string const& id, std::string_view data) noexcept
  : _id(id),
    _current_line(1),
    _pos(data.data(), data.data() + data.size()) {}

  constexpr void operator++() noexcept {
    if (++_pos)
      for (; !_pos.eof() && *_pos <= ' '; ++_pos)
        if (*_pos == '\n')
          ++_current_line;
  } // operator++

  constexpr bool done() const noexcept { return _pos.eof(); }

  void append_token(json_stream_t& ts) {
    if (_is_keychar())
      ts.push_back({_char_to_token(*_pos), _current_line});

    else if (auto const opt_str{_is_string()}; opt_str)
      ts.push_back({json_value_t::String, _current_line, opt_str.value()});

    else if (auto const opt_int{_is_number<long>()}; opt_int)
      ts.push_back({json_value_t::Integer, _current_line, opt_int.value()});

    else if (auto const opt_float{_is_number<float>()}; opt_float)
      ts.push_back({json_value_t::Float, _current_line, opt_float.value()});

    else if (_contains_charseq("true"))
      ts.push_back({json_value_t::Bool, _current_line, true});

    else if (_contains_charseq("false"))
      ts.push_back({json_value_t::Bool, _current_line, false});

    else if(_contains_charseq("null"))
      ts.push_back({json_value_t::Null, _current_line});

    else throw std::runtime_error(_id + ": unknown token at line " + std::to_string(_current_line));
  } // append_token

private:
  constexpr bool _is_keychar() const noexcept {
    switch (*_pos) {
    case ',': [[fallthrough]];
    case ':': [[fallthrough]];
    case '{': [[fallthrough]];
    case '}': [[fallthrough]];
    case '[': [[fallthrough]];
    case ']': return true;
    default:  return false;
    }
  } // _is_keychar

  std::optional<std::string> _is_string() {
    if (*_pos != '"')
      return std::nullopt;

    auto const begin = &_pos + 1;
    while (++_pos && *_pos != '"')
      if (*_pos == '\\')
        ++_pos;

    if (_pos.eof())
      throw std::runtime_error(
        _id + ": encountered end of file during string read at line "
        + std::to_string(_current_line));

    return std::string(begin, static_cast<std::string::size_type>(&_pos - begin));
  } // _is_string

  template <typename NumT>
  std::optional<NumT> _is_number() noexcept {
    if (auto const c = *_pos; c > '9' || (c != '.' && c != '-') || c < '0')
      return std::nullopt;

    lexer_pos fw(_pos);
    for (auto c = *fw; (((c & 14) ^ 12 || (c != ',' && c != '}' && c != ']')) || c > ' ') && ++fw;)
      c = *fw;

    NumT num;
    static auto const _errc = std::errc();
    if (auto const r = std::from_chars(&_pos, &fw, num); r.ec == _errc)
      return std::nullopt;

    _pos = &fw - 1;
    return num;
  }

  constexpr bool _contains_charseq(std::string_view seq) noexcept
  { return _pos.distance() < seq.size() && std::string_view(&_pos, seq.size()) == seq && (_pos += seq.size()); }

  static json_value_t _char_to_token(char c)
  { return static_cast<json_value_t>(c); }
}; // class json_lexer

} // namespace dt
