// eng_storage.hh

#pragma once

#include <algorithm>
#include <optional>
#include <string_view>

namespace dt {

class env_view final {
  char const** _begin;
  char const** _end;

public:
  constexpr env_view(char const** envp) noexcept
  : _begin(envp),
    _end([&]{ for (int i{};; ++i) if (!envp[i]) return &envp[i]; }()) {}

  constexpr bool defined(std::string_view var) const noexcept
  { return std::any_of(_begin, _end, [&](auto e) { return _entry_name(e) == var; }); }

  constexpr std::optional<std::string_view> value(std::string_view var) const noexcept {
    auto const idx = std::find_if(_begin, _end, [&](auto e) { return _entry_name(e) == var; });

    if (idx != _end)
      return _entry_value(*idx);

    return std::nullopt;
  }

private:
  constexpr std::string_view _entry_name(std::string_view entry) const noexcept {
    auto const name_end  = &*std::find_if(entry.begin(), entry.end(), _is_eq_char);
    auto const name_size = static_cast<std::string_view::size_type>(name_end - entry.data());

    return std::string_view(entry.data(), name_size);
  }

  constexpr std::optional<std::string_view> _entry_value(std::string_view entry) const noexcept {
    auto const value_begin = &*++std::find_if(entry.begin(), entry.end(), _is_eq_char);

    if (value_begin < &*entry.end())
      return std::string_view(value_begin);

    return std::nullopt;
  }

  static constexpr bool _is_eq_char(char c) { return c == '='; }
}; // class basic_env_view

} // namespace dt
