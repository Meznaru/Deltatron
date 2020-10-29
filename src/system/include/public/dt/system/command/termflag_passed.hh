// termflag_passed.hh

#pragma once

#include <exception>
#include <string>

namespace dt {

class termflag_passed final : public std::exception {
  std::string _msg{};

public:
  termflag_passed(std::string const& message) noexcept
  : std::exception{},
    _msg(message) {}

  char const* what() const noexcept override { return _msg.c_str(); }
};

}
