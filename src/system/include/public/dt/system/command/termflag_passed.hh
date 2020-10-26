// term_flag_passed.hh

#pragma once

#include <string>

namespace dt {

struct termflag_passed final {
  std::string msg{};

  termflag_passed(std::string const& message) noexcept
  : msg(message) {}
};

}
