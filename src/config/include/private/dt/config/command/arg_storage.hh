// arg_storage.hh

#pragma once

#include <algorithm>

#include <cstring>

namespace dt {

class arg_storage final {
  char const* const* const _av_start;
  char const* const* const _av_end;

public:
  constexpr arg_storage(int ac, char const** av) noexcept
  : _av_start(av),
    _av_end(&av[ac]) {}

  constexpr bool contains(char const* v) const noexcept
  { return std::any_of(_av_start, _av_end, [&v](auto const& a) { return !std::strcmp(v, a); }); }

  constexpr char const* arg_next_to(char const* v) const noexcept {
    auto const vloc = std::find_if(_av_start, _av_end, [&v](auto const& a) { return !std::strcmp(v, a); });

    return vloc < _av_end - 1 ? vloc[1]: nullptr;
  }
}; // class arg_storage

}
