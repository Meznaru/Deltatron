// json_lexer.hh

#pragma once

#include <dt/json/container/value.hh>

#include <charconv>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <cstddef>

namespace dt {

class json_lexer final {

  class lexer_pos final {
    char const* _end;
    char const* _curr;

  public:
    constexpr lexer_pos(char const* begin, char const* end) noexcept
    : _end(end),
      _curr(begin) {}

    constexpr lexer_pos(lexer_pos const& lp) noexcept
    : _end(lp._end),
      _curr(lp._curr) {}

    constexpr auto eof()       const noexcept { return _curr == _end; }
    constexpr auto operator*() const noexcept { return *_curr;        }
    constexpr auto operator&() const noexcept { return _curr;         }

    constexpr lexer_pos& operator++() noexcept
    { if (_curr != _end) ++_curr; return *this; }

    constexpr void operator=(char const* p) noexcept
    { _curr = p; }

    constexpr auto distance() const noexcept
    { return static_cast<std::size_t>(_end - _curr); }

    constexpr bool operator+=(std::size_t n) noexcept
    { return static_cast<bool>(_curr += n); }
  }; // class lexer_pos


  std::string const& _id;
  std::size_t        _line;
  lexer_pos          _pos;

public:
  static json_stream_t create_token_stream(std::string const& id, std::string_view data) {
    json_stream_t stream{};

    for (json_lexer lx(id, data); !lx._done(); ++lx)
      lx._append_token(stream);

    _print_stream(id, stream);

    return stream;
  }

private:
  constexpr json_lexer(std::string const& id, std::string_view data) noexcept
  : _id(id),
    _line(1),
    _pos(data.data(), data.data() + data.size()) {}

  constexpr void operator++() noexcept {
    if ((++_pos, !_pos.eof()))
      for (; !_pos.eof() && *_pos <= ' '; ++_pos)
        if (*_pos == '\n')
          ++_line;
  }

  constexpr bool _done() const noexcept { return _pos.eof(); }

  void _append_token(json_stream_t& ts) {
    if (_is_keychar()) ts.push_back({_char_to_token(*_pos), _line});

    else if (auto const opt_str{_is_string()}; opt_str)
      ts.push_back({json_t::String , _line, opt_str.value()});

    else if (auto const opt_int{_is_number<int>()}; opt_int)
      ts.push_back({json_t::Integer, _line, opt_int.value()});

    else if (auto const opt_float{_is_number<float>()}; opt_float)
      ts.push_back({json_t::Float, _line, opt_float.value()});

    else if (_contains_charseq("true"))
      ts.push_back({json_t::Bool, _line, true });

    else if (_contains_charseq("false"))
      ts.push_back({json_t::Bool, _line, false});

    else if(_contains_charseq("null"))
      ts.push_back({json_t::Null, _line});

    else throw std::runtime_error(_id + ": unknown value at line " + std::to_string(_line));
  }

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
  }

  std::optional<std::string> _is_string() {
    if (*_pos != '"')
      return std::nullopt;

    auto const begin = (++_pos, &_pos);
    while (*_pos != '"' && (++_pos, !_pos.eof()))
      if (*_pos == '\\')
        ++_pos;

    if (_pos.eof())
      throw std::runtime_error(
        _id + ": encountered end of file during string evaluation at line " + std::to_string(_line));

    return std::string(begin, &_pos);
  }

  template <typename NumT>
  std::optional<NumT> _is_number() noexcept {
    if (char const c{*_pos}; c > '9' || (c < '0' && c != '.' && c != '-'))
      return std::nullopt;

    lexer_pos fw(_pos);
    for (char c{*fw}; c > ' ' && c != ',' && c != '}' && c != ']' && !fw.eof();)
      (++fw, c = *fw);

    if (NumT num; std::from_chars(&_pos, &fw, num).ec != std::errc())
      return (_pos = &fw - 1, num);

    return std::nullopt;
  }

  constexpr bool _contains_charseq(std::string_view seq) noexcept
  { return _pos.distance() < seq.size() && std::string_view(&_pos, seq.size()) == seq && (_pos += seq.size()); }

  constexpr json_t _char_to_token(char c) { return static_cast<json_t>(c); }

  static void _print_stream(std::string const& id, json_stream_t const& ts) {

    std::cout << "json data stream for \"" + id + "\":\n";

    for (auto const& t : ts)
      switch (t.type()) {
        case json_t::String:
          std::cout << "\tstring:" << t.opt_val<std::string>().value() << "\n";
          break;
        case json_t::Integer:
          std::cout << "\tinteger:" << t.opt_val<int>().value() << "\n";
          break;
        case json_t::Float:
          std::cout << "\tfloat:" << t.opt_val<float>().value() << "\n";
          break;
        case json_t::Bool:
          std::cout << "\tbool:" << t.opt_val<bool>().value() << "\n";
          break;
        case json_t::LBrace:
          std::cout << "\tLBrace:'{'\n";
          break;
        case json_t::RBrace:
          std::cout << "\tRBrace:'}'\n";
          break;
        case json_t::LBrack:
          std::cout << "\tLBrack:'['\n";
          break;
        case json_t::RBrack:
          std::cout << "\tRBrack:']'\n";
          break;
        case json_t::Comma:
          std::cout << "\tComma:','\n";
          break;
        case json_t::Colon:
          std::cout << "\tColon:':'\n";
          break;
        case json_t::Null:
          std::cout << "\tNull:'null'\n";
          break;
        default:
          std::cout << "";
      }
  }
}; // class json_lexer

} // namespace dt
