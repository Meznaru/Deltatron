// directory.hh

#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace dt {

class filesystem;

class directory final {
  std::string      _path;
  directory const* _parent;

  friend class ::dt::filesystem;

public:
  auto parent() const noexcept -> std::optional<directory>;
  auto name()   const noexcept -> std::string;

  auto mkdir(std::string const& name) const -> directory;
  auto chdir(std::string const& name) const -> directory;

  auto fload(std::string const& name)                         const -> std::optional<std::string>;
  auto fwrite(std::string const& name, std::string_view data) const -> void;

private:
  directory(std::string const& path, directory const* parent) noexcept;
};

}
