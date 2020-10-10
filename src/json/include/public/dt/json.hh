// json.hh

#pragma once

#include <dt/json/container.hh>

namespace dt {

class json final {
  std::string    _id;
  json_container _root;

public:
  json(std::string id, std::string_view data)
  : _id(id),
    _root(_parse_stream(data)) {}

  json_container const& root() const noexcept { return _root; }

private:
  json_container _parse_stream(std::string_view) const;
};

}
