// parser.hh

#pragma once

#include <dt/json/container.hh>

#include <string>

namespace dt {

class json_parser final {
  std::string             const& _id;
  json_value::stream_type const& _ts;

public:
  json_parser(std::string const& id, json_value::stream_type const& ts)
  : _id(id),
    _ts(ts)
  {
    // verify token stream here
  }

  json_container create_container_tree() {
    json_container::object_type root_obj{};

    for (auto const& t : _ts)
      ;


    return json_container(_id, json_value_t::Object, root_obj);
  }

};

}
