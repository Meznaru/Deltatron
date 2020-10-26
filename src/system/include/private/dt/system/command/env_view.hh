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
    auto idx = std::find_if(_begin, _end, [&](auto e) { return _entry_name(e) == var; });

    if (idx == _end)
      return std::nullopt;

    return _entry_value(*idx);
  }

private:
  constexpr std::string_view _entry_name(std::string_view entry) const noexcept {
    auto name_end  = _name_value_border(entry);
    auto name_size = static_cast<std::string_view::size_type>(&*name_end - entry.data());

    return std::string_view(entry.data(), name_size);
  }

  constexpr std::optional<std::string_view> _entry_value(std::string_view entry) const noexcept {
    auto value_begin = _name_value_border(entry) + 1;

    if (value_begin == entry.end())
      return std::nullopt;

    return std::string_view(&*value_begin);
  }

  constexpr std::string_view::const_iterator _name_value_border(std::string_view entry) const noexcept
  { return std::find_if(entry.begin(), entry.end(), [](char c) { return c == '='; }); }
}; // class basic_env_view

} // namespace dt
