// semantic_analysis.hh

#pragma once

#include <dt/json/container/value.hh>

#include <stdexcept>

namespace dt {

class json_semantic_analysis final {

  class stream_pos final {
    json_value const* _curr;
    json_value const* _end;
    std::size_t       _obj_depth;
    std::size_t       _arr_depth;

  public:
    stream_pos(json_stream_t const& ts)
    : _curr(ts.data()),
      _end(ts.data() + ts.size()),
      _obj_depth(1),
      _arr_depth(1) {}

    constexpr bool eof() const noexcept { return _curr == _end; }

    constexpr std::size_t& obj_depth() noexcept { return _obj_depth; }
    constexpr std::size_t& arr_depth() noexcept { return _arr_depth; }

    constexpr bool type_is(json_t t) const noexcept { return _curr->type() == t; }

    constexpr stream_pos& operator++() noexcept
    { if(_curr < _end) ++_curr; return *this; }

    constexpr json_value const& operator*()  const noexcept { return *_curr; }
    constexpr json_value const* operator->() const noexcept { return _curr;  }
    constexpr json_value const* operator&()  const noexcept { return _curr;  }
  };

  std::string const& _id;

public:
  static void verify_stream(std::string const& id, json_stream_t const& ts) {
    stream_pos pos(ts);

    if (pos.eof())
      return;

    if (pos.type_is(json_t::LBrace)) {
      ++pos.obj_depth();
      ++pos;
    }

    for (json_semantic_analysis root(id); !pos.eof(); ++pos) {
      if (pos->type() == json_t::String)
        root._verify_object_entry(++pos);

      else if (pos->type() == json_t::RBrace)
        --pos.obj_depth();

      else throw std::runtime_error(id + ": expected object key value or termination of object at line " + std::to_string(pos->line()));
    }

    if (pos.obj_depth() > 1) throw std::runtime_error(id + ": missing '}' detected after scanning file");
    if (pos.obj_depth() < 1) throw std::runtime_error(id + ": missing '{' detected after scanning file");
    if (pos.arr_depth() > 1) throw std::runtime_error(id + ": missing ']' detected after scanning file");
    if (pos.arr_depth() < 1) throw std::runtime_error(id + ": missing '[' detected after scanning file");
  }

private:
  json_semantic_analysis(std::string const& id)
  : _id(id) {}

  void _verify_object_entry(stream_pos& pos) {
    if (pos.eof() || !pos.type_is(json_t::Colon))
      throw std::runtime_error(_id
        + ": expected ':' after \"" + (&pos - 1)->opt_val<std::string>().value() + "\" at line "
        +  std::to_string(pos->line()));

    _verify_index(++pos);
  }

  void _verify_index(stream_pos& pos) {
    if (pos.eof())
      throw std::runtime_error(_id + ": expected json value at line " + std::to_string(pos->line()));

    switch (pos->type()) {
    case json_t::String:  [[fallthrough]];
    case json_t::Integer: [[fallthrough]];
    case json_t::Float:   [[fallthrough]];
    case json_t::Bool:    [[fallthrough]];
    case json_t::Null:
      ++pos;
      break;
    case json_t::LBrace:
      ++pos.obj_depth();
      _verify_object(++pos);
      break;
    case json_t::LBrack:
      ++pos.arr_depth();
      _verify_array(++pos);
      break;
    case json_t::Comma:
      throw std::runtime_error(_id + ": invalid comma at line " + std::to_string(pos->line()));
    case json_t::Colon:
      throw std::runtime_error(_id + ": invalid colon at line " + std::to_string(pos->line()));
    case json_t::RBrack:
      throw std::runtime_error(_id + ": invalid ']' at line " + std::to_string(pos->line()));
    case json_t::RBrace:
      throw std::runtime_error(_id + ": invalid '}' at line " + std::to_string(pos->line()));
    default:
      throw std::runtime_error(_id + ": invalid data at line " + std::to_string(pos->line()));
    }

    // if (c->type() == )
  }

  void _verify_object(stream_pos&) {}

  void _verify_array(stream_pos&) {}

};

}
