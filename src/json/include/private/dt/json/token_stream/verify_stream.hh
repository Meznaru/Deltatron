// check_stream.hh

#pragma once

#include <dt/json/token_stream/token.hh>

#include <string_view>

namespace dt {

class verify_stream final {
  std::string_view const _id;
  token const*           _read_head;
  token const*     const _end;

public:
  verify_stream(std::string_view const& id, token_stream_t const& ts)
  : _id(id),
    _read_head(&*ts.begin()),
    _end(&*ts.end())
  {

  }

private:

  constexpr bool _stream_end() const noexcept { return _read_head == _end; }

  void _verify_object() {}
  
  void _verify_array() {}
  
  void _verify_object_member() {}

  void _verify_array_element() {}

};

}
