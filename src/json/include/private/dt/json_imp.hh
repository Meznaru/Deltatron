// json_imp.hh

#pragma once

#include <dt/json/token/token_stream.hh>

#include <string>
#include <string_view>

namespace dt {

class json_imp final {
  std::string _id;

public:
  json_imp(std::string const& id, std::string_view const& data)
  : _id(id) {}
};

}
