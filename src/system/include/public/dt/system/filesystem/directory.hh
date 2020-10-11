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
  std::optional<directory> parent() const noexcept;

  directory operator/(std::string name) const;

  std::optional<std::string> fload(std::string name) const;

  void fwrite(std::string name, std::string_view data) const;

private:
  directory(std::string const& path, directory const* parent) noexcept;
};

}
