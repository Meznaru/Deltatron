// parser.hh

#pragma once

#include <dt/json/container.hh>

#include <string>

namespace dt {

class json_parser final {
  using stream_iterator = json_stream_t::const_iterator;

  std::string   const& _id;
  json_stream_t const& _ts;

public:
  constexpr json_parser(std::string const& id, json_stream_t const& ts) noexcept
  : _id(id),
    _ts(ts)
  {
    // TODO: move stream verification here; provide source file for verify_stream implementation
  }

  json_object_type create_root_object() const noexcept {
    json_object_type root_obj{};

    for (stream_iterator t = _ts.begin(); t < _ts.end() || t->type() != json_value_t::RBrace; ++t)
      if (t->type() == json_value_t::String) {
        auto const& key   = t->string_value();
        auto const  value = _get_index(t += 2);
        root_obj.insert({key, value});
      }

    return root_obj;
  }

private:
  json_type _get_index(stream_iterator& t) const noexcept {
    switch (t->type()) {
    case json_value_t::LBrace:
      return _create_object(++t);
    case json_value_t::LBrack:
      return _create_array(++t);
    default:
      auto const c = t++;
      return *c;
    }
  }

  json_container _create_object(stream_iterator& t) const noexcept {
    json_object_type obj{};

    for (; t->type() != json_value_t::RBrace; ++t)
      if (t->type() == json_value_t::String) {
        auto const& key   = t->string_value();
        auto const  value = _get_index(t += 2);
        obj.insert({key, value});
      }

    return {_id, json_value_t::Object, obj};
  }

  json_container _create_array(stream_iterator& t) const noexcept {
    json_array_type arr{};

    if (t->type() != json_value_t::RBrack) {
      auto const value = _get_index(t);
      arr.push_back(value);
      ++t;
    }

    for (; t->type() != json_value_t::RBrack; ++t)
      if (t->type() == json_value_t::Comma) {
        auto const& value = _get_index(t += 1);
        arr.push_back(value);
      }

    return {_id, json_value_t::Array, arr};
  }
};

}
