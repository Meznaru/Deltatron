// container.hh

#pragma once

#include <dt/json/container/type.hh>

#include <optional>
#include <string>

#include <cstddef>

namespace dt {

class json;

class json_container_imp;

class json_container final {
public:
  friend class ::dt::json;

private:
  json_container_imp const& _container;

public:
  auto type() const noexcept -> json_t;

  auto type_at(std::string const&)      const noexcept -> json_t;
  auto container_at(std::string const&) const noexcept -> std::optional<json_container>;
  auto string_at(std::string const&)    const noexcept -> std::optional<std::string>;
  auto int_at(std::string const&)       const noexcept -> std::optional<int>;
  auto float_at(std::string const&)     const noexcept -> std::optional<float>;
  auto bool_at(std::string const&)      const noexcept -> std::optional<bool>;

  auto type_at(std::size_t)             const noexcept -> json_t;
  auto container_at(std::size_t)        const noexcept -> std::optional<json_container>;
  auto string_at(std::size_t)           const noexcept -> std::optional<std::string>;
  auto int_at(std::size_t)              const noexcept -> std::optional<int>;
  auto float_at(std::size_t)            const noexcept -> std::optional<float>;
  auto bool_at(std::size_t)             const noexcept -> std::optional<bool>;

private:
  json_container(json_container_imp const&) noexcept;
};

}
