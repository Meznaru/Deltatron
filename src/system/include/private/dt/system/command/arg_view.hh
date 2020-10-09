// arg_storage.hh

#pragma once

#include <algorithm>
#include <optional>
#include <string_view>

namespace dt {

class arg_view final {
  char const** _begin;
  char const** _end;

public:
  constexpr arg_view(int ac, char const** av) noexcept
  : _begin(av),
    _end(&av[ac]) {}

  constexpr bool contains(std::string_view v) const noexcept
  { return std::any_of(_begin, _end, [&v](std::string_view a) { return v == a; }); }

  constexpr std::optional<std::string_view> arg_next_to(std::string_view v) const noexcept {
    auto const vloc = std::find_if(_begin, _end, [&v](std::string_view a) { return v == a; });

    if (vloc < _end - 1)
      return std::string_view(vloc[1]);

    return std::nullopt;
  }
}; // class arg_storage

}
