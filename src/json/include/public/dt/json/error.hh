// error.hh

#pragma once

#include <exception>
#include <string>

#include <cstddef>

namespace dt {

class json_error final : public std::exception {
  std::string _msg;

public:
  json_error(std::string id, std::size_t line, std::string err) noexcept
  : std::exception{},
    _msg(std::string("json error in \"") + id + "\" at line " + std::to_string(line) + ": " + err) {}

  json_error(std::string const& id, std::string const& err) noexcept
  : std::exception{},
    _msg(std::string("json error in \"" + id + "\": " + "\"" + err + "\"")) {}

  char const* what() const noexcept override { return _msg.c_str(); }
};

}
