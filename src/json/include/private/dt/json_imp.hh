// json_imp.hh

#include <dt/json/parser.hh>
#include <dt/json/container_imp.hh>

#include <string>
#include <string_view>

namespace dt {

class json_imp final {
  std::string        _id;
  json_container_imp _root;

public:
  json_imp(std::string id, std::string_view data)
  : _id(id),
    _root(json_parser::parse_stream(_id, data)) {}

  json_container_imp& root_ref() noexcept { return _root; }
};

}
