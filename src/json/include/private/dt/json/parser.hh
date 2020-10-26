// parser.hh

#pragma once

#include <dt/json/container/value.hh>
#include <dt/json/parser/lexer.hh>
#include <dt/json/parser/semantic_analysis.hh>

#include <dt/json/container_imp.hh>

#include <string>
#include <string_view>

namespace dt {

class json_parser final {
  using iter_t = json_value const*;

  iter_t _begin;
  iter_t _end;

public:
  static dt::json_container_imp parse_stream(std::string const& id, std::string_view data)
  { return json_parser(id, json_lexer::create_token_stream(id, data))._create_root_object(); }

private:
  json_parser(std::string const& id, json_stream_t const& ts) noexcept
  : _begin(ts.data()),
    _end(ts.data() + ts.size())
  { json_semantic_analysis::verify_stream(id, ts); }

  json_container_imp _create_root_object() const noexcept {
    json_object_type root_obj{};

    for (iter_t t = _begin; t < _end && t->type() != json_t::RBrace; ++t)
      if (t->type() == json_t::String)
        root_obj.insert({t->opt_val<std::string>().value(), _get_index(t += 2)});

    return {json_t::Object, root_obj};
  }

  json_type _get_index(iter_t& t) const noexcept {
    switch (t->type()) {
    case json_t::LBrace:
      return _create_object(++t);
    case json_t::LBrack:
      return _create_array(++t);
    default:
      auto const v = t++;
      return *v;
    }
  }

  json_container_imp _create_object(iter_t& t) const noexcept {
    json_object_type obj{};

    for (; t->type() != json_t::RBrace; ++t)
      if (t->type() == json_t::String)
        obj.insert({t->opt_val<std::string>().value(), _get_index(t += 2)});

    return {json_t::Object, obj};
  }

  json_container_imp _create_array(iter_t& t) const noexcept {
    json_array_type arr{};

    if (t->type() != json_t::RBrack)
      arr.push_back(_get_index(t));

    for (; t->type() != json_t::RBrack; ++t)
      if (t->type() == json_t::Comma)
        arr.push_back(_get_index(++t));

    return {json_t::Array, arr};
  }
}; // class json_parser

} // namespace dt
