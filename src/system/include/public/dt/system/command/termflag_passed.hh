// term_flag_passed.hh

#pragma once

#include <string>

namespace dt {

struct termflag_passed final {
  std::string const msg{};

  termflag_passed(std::string const& message) noexcept
  : msg(message) {}
};

}
