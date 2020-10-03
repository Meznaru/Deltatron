// stream_lexer.hh

#pragma once

#include <dt/json/token_stream/token.hh>

#include <charconv>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>

namespace dt {

class lexer_pos final {
  char const* const _end;
  char const*       _read_head;

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

class stream_lexer final {
  std::string_view const _id;
  std::size_t            _current_line;
  lexer_pos              _pos;

public:
  constexpr stream_lexer(std::string_view const& id, std::string_view const& data) noexcept
  : _id(id),
    _current_line(1),
    _pos(&*data.begin(), &*data.end()) {}

  constexpr void operator++() noexcept {
    if (++_pos)
      for (; !_pos.eof() && *_pos <= ' '; ++_pos)
        if (*_pos == '\n')
          ++_current_line;
  } // operator++

  constexpr bool done() const noexcept { return _pos.eof(); }

  void append_token(token_stream_t& ts) {
    if (_is_keychar())
      ts.push_back({token::char_to_token(*_pos), _current_line});

    else if (auto const ptr_str{_is_string()}; ptr_str)
      ts.push_back({token_id::String, _current_line, *ptr_str});

    else if (auto const ptr_int{_is_number<int>()}; ptr_int)
      ts.push_back({token_id::Integer, _current_line, *ptr_int});

    else if (auto const ptr_float{_is_number<float>()}; ptr_float)
      ts.push_back({token_id::Float, _current_line, *ptr_float});

    else if (_contains_charseq("true", 4))
      ts.push_back({token_id::Bool, _current_line, true});

    else if (_contains_charseq("false", 5))
      ts.push_back({token_id::Bool, _current_line, false});

    else if(_contains_charseq("null", 4))
      ts.push_back({token_id::Null, _current_line});

    else throw std::runtime_error(std::string(_id) + ": unknown token at line " + std::to_string(_current_line));
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

  std::string_view const* _is_string() {
    if (*_pos != '"')
      return nullptr;

    static std::string_view sv;

    auto const begin = &_pos + 1;
    while (++_pos && *_pos != '"')
      if (*_pos == '\\')
        ++_pos;

    if (_pos.eof())
      throw std::runtime_error(
        std::string(_id)
        + ": encountered end of file during string read at line "
        + std::to_string(_current_line));

    sv = std::string_view(begin, static_cast<std::size_t>(&_pos - begin));

    return &sv;
  } // _is_string

  template <typename NumT>
  NumT const* _is_number() noexcept {
    if (auto const c = *_pos; c > '9' || (c != '.' && c != '-') || c < '0')
      return nullptr;

    lexer_pos fw(_pos);
    for (auto c = *fw; (((c & 14) ^ 12 || (c != ',' && c != '}' && c != ']')) || c > ' ') && ++fw;)
      c = *fw;

    static NumT num;
    static auto const _errc = std::errc();
    if (auto const r = std::from_chars(&_pos, &fw, num); r.ec == _errc)
      return nullptr;

    _pos = &fw - 1;
    return &num;
  }

  constexpr bool _contains_charseq(char const* seq, std::size_t const seq_sz) noexcept
  { return _pos.distance() < seq_sz && std::string_view(&_pos, seq_sz) == seq && (_pos += seq_sz); }
}; // class stream_lexer

} // namespace dt
