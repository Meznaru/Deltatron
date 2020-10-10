// verify_stream.hh

#pragma once

#include <dt/json/container/value.hh>

#include <stdexcept>

namespace dt {

struct json_verify_state final {
  std::string                   const& id;
  json_stream_t                 const& ts;
  std::size_t                          obj_depth;
  std::size_t                          arr_depth;
  json_stream_t::const_iterator        curr;

  json_verify_state(std::string const& id, json_stream_t const& ts)
  : id(id),
    ts(ts),
    obj_depth(1),
    arr_depth(1),
    curr(ts.begin()) {}
};

void verify_object(json_verify_state&);
void verify_object_entry(json_verify_state&);
void verify_array(json_verify_state&);
void verify_index(json_verify_state&);

void verify_stream(std::string const& id, json_stream_t const& ts) {
  json_verify_state state(id, ts);
  auto& c = state.curr;

  if (c->type() == json_value_t::LBrace) {
    ++state.obj_depth;
    ++c;
  }

  for (; c < state.ts.end(); ++c) {
    switch (c->type()) {
    case json_value_t::String:
      verify_object_entry(state);
      break;
    case json_value_t::RBrace:
      --state.obj_depth;
      break;
    default:
      throw std::runtime_error(state.id + ": expected entry or termination of object at line " + std::to_string(c->line()));
    }
  }

  if (state.obj_depth > 1)
    throw std::runtime_error(state.id + ": missing '}' detected after scanning file");

  if (state.obj_depth < 1)
    throw std::runtime_error(state.id + ": missing '{' detected after scanning file");
}

// state.cur pointing to string type
void verify_object_entry(json_verify_state& state) {
  auto& c = state.curr;

  ++c;

  if (c->type() != json_value_t::Colon)
    throw std::runtime_error(state.id + ": missing ':' detected for object entry at line " + std::to_string(c->line()));

  ++c;

  verify_index(state);

  if (c->type() == json_value_t::RBrace) {
    --state.obj_depth;
    ++c;
    return;
  }

  if (c->type() == json_value_t::Comma) {
    ++c;
    verify_index(state);
    return;
  }

  throw std::runtime_error(state.id + ": missing '}' at line " + std::to_string(c->line()));
}

void verify_index(json_verify_state& state) {
  auto& c = state.curr;

  if (c->type() == json_value_t::LBrace) {
    verify_object(state);
  }
}

void verify_object(json_verify_state&) {}

}
