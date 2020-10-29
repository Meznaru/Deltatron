// semantic_analysis.hh

#pragma once

#include <dt/json/container/value.hh>
#include <dt/json/error.hh>

namespace dt {

class json_semantic_analysis final {

  class stream_pos final {
    json_value const* _curr;
    json_value const* _end;

  public:
    stream_pos(json_stream_t const& ts)
    : _curr(ts.data()),
      _end(ts.data() + ts.size()) {}

    constexpr bool eof() const noexcept { return _curr == _end; }

    constexpr json_value const& operator*()  const noexcept { return *_curr; }
    constexpr json_value const* operator->() const noexcept { return _curr;  }
    constexpr json_value const* operator&()  const noexcept { return _curr;  }

    constexpr stream_pos& operator++() noexcept
    { if(_curr < _end) ++_curr; return *this; }
  };

  std::string const& _id;

public:
  static void verify_stream(std::string const& id, json_stream_t const& ts) {
    auto const check_end = [&](stream_pos& p) {
      if (p.eof()) throw json_error(id, "end of file reached while evaluating root object");
    };

    stream_pos pos(ts);

    if (pos.eof())
      return;

    if (pos->type() == json_t::LBrace) {
      check_end(++pos);

      if (pos->type() == json_t::RBrace) {
        ++pos;

        if (!pos.eof())
          throw json_error(id, "extraneous data detected after json root object");

        return;
      }
    }

    for (json_semantic_analysis root(id);;) {
      if (pos->type() != json_t::String)
        throw json_error(id, pos->line(), "expected string value for root object key");

      check_end(++pos);

      if (pos->type() != json_t::Colon)
        throw json_error(id, pos->line(), "no ':' appending root object key");

      check_end(++pos);

      root._verify_index(pos);

      ++pos;

      if (pos.eof())
        return;

      if (pos->type() == json_t::RBrace) {
        ++pos;

        if (!pos.eof())
          throw json_error(id, "extraneous data detected after json root object");

        return;
      }

      if (pos->type() != json_t::Comma)
        throw json_error(id, pos->line(), "no comma at end of root object value");

      check_end(++pos);
    }
  }

private:
  json_semantic_analysis(std::string const& id)
  : _id(id) {}

  void _verify_index(stream_pos& pos) const {
    if (pos.eof())
      throw json_error(_id, "end of file reached while evaluating index");

    switch (pos->type()) {
    case json_t::String:  [[fallthrough]];
    case json_t::Integer: [[fallthrough]];
    case json_t::Float:   [[fallthrough]];
    case json_t::Bool:    [[fallthrough]];
    case json_t::Null:    break;
    case json_t::LBrace:  _verify_object(++pos); break;
    case json_t::LBrack:  _verify_array(++pos);  break;
    case json_t::Comma:   throw json_error(_id, pos->line(), "invalid ',' detected");
    case json_t::Colon:   throw json_error(_id, pos->line(), "invalid ':' detected");
    case json_t::RBrack:  throw json_error(_id, pos->line(), "invalid ']' detected");
    case json_t::RBrace:  throw json_error(_id, pos->line(), "invalid '}' detected");
    default:              throw json_error(_id, pos->line(), "invalid data detected");
    }
  }

  void _verify_object(stream_pos& pos) const {
    auto const check_end = [&](stream_pos& p) {
      if (p.eof()) throw json_error(_id, "end of file reached while evaluating object");
    };

    check_end(pos);

    if (pos->type() == json_t::RBrace)
      return;

    for (;;) {
      if (pos->type() != json_t::String)
        throw json_error(_id, pos->line(), "expected string value for object key");

      check_end(++pos);

      if (pos->type() != json_t::Colon)
        throw json_error(_id, pos->line(), "no ':' appending object key");

      check_end(++pos);

      _verify_index(pos);

      check_end(++pos);

      if (pos->type() == json_t::RBrace)
        break;

      if (pos->type() != json_t::Comma)
        throw json_error(_id, pos->line(), "no comma at end of object value");

      check_end(++pos);
    }
  }

  void _verify_array(stream_pos& pos) const {
    auto const check_end = [&](stream_pos& p) {
      if (p.eof()) throw json_error(_id, "end of file reached while evaluating array");
    };

    check_end(pos);

    if (pos->type() == json_t::RBrack)
      return;

    for (;;) {
      _verify_index(pos);

      check_end(++pos);

      if (pos->type() == json_t::RBrack)
        break;

      if (pos->type() != json_t::Comma)
        throw json_error(_id, pos->line(), "no comma at end of array index");

      check_end(++pos);
    }
  }
};

}
