// json_imp.hh

#pragma once

#include <dt/json/token_stream.hh>

#include <string>
#include <string_view>

namespace dt {

class json_imp final {
  std::string    const _id;
  token_stream_t const _stream;

public:
  json_imp(std::string const& id, std::string_view const& data)
  : _id(id),
    _stream(manifest_token_stream(id, data)) {}
};

}
