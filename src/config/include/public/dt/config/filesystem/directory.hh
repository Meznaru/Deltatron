// directory.hh

#pragma once

#include <string>

namespace dt {

class filesystem;

class directory final {
public:
  struct file_init final {
    char const* const name;
    char const* const data = nullptr;
    std::size_t const size = 0;
  };

  friend class ::dt::filesystem;

private:
  directory const* const _parent;
  std::string      const _path;

public:
  directory const* parent() const noexcept;

  directory load_directory(char const* dirname) const;

  std::string load_file(file_init file) const;

  void write_file(file_init file) const;

private:
  directory(std::string const& path, directory const* parent) noexcept;
};

}
