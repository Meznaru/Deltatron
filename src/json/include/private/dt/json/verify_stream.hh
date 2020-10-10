// verify_stream.hh

#pragma once

#include <dt/json/container/value.hh>

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

void verify_stream(std::string const& id, json_stream_t const& ts) {
  if (ts.empty())
    return;

  json_verify_state state(id, ts);

}

}
