// eng_storage.hh

#pragma once

#include <cstring>

namespace dt {

class env_storage final {
  char const* const* const _envp;

public:
  constexpr env_storage(char const** envp) noexcept
  : _envp(envp) {}

  constexpr char const* value(char const* var) const noexcept {
    for (int i{}; _envp[i]; ++i)
      if (_env_match_env_entry(_envp[i], var))
        return _env_entry_value(_envp[i]);

    return nullptr;
  }

  constexpr bool defined(char const* var) const noexcept {
    for (int i{}; _envp[i]; ++i)
      if (_env_match_env_entry(_envp[i], var))
        return true;

    return false;
  }

private:
  constexpr char const* _env_entry_value(char const* env_entry) const noexcept {
    auto begin = env_entry;

    while (*begin && *begin != '=')
      ++begin;

    return (!*begin || !*(++begin)) ? nullptr : begin;
  }

  constexpr bool _env_match_env_entry(char const* env_entry, char const* var) const noexcept {
    decltype(sizeof(0)) nsz{};

    for (; env_entry[nsz] && var[nsz] && env_entry[nsz] != '='; ++nsz)
      if (env_entry[nsz] != var[nsz])
        return false;

    return nsz == std::strlen(var);
  }
};

}
