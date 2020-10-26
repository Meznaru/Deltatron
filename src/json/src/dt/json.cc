// json.cc

#include <dt/json.hh>
#include <dt/json_imp.hh>

#include <dt/json/container.hh>
#include <dt/json/container_imp.hh>

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

#include <cstddef>

dt::json::json(std::string id, std::string_view data)
: _json(std::make_unique<json_imp>(id, data)) {}

dt::json::~json() noexcept {}

dt::json_container dt::json::root() const noexcept
{ return {_json->root_ref()}; }

dt::json_container::json_container(json_container_imp const& c) noexcept
: _container(c) {}

dt::json_t dt::json_container::type() const noexcept
{ return _container.type(); }

dt::json_t dt::json_container::type_at(std::string const& k) const noexcept
{ return _container.type_at(k); }

std::optional<int> dt::json_container::int_at(std::string const& k) const noexcept
{ return _container.value_at<int>(k); }

std::optional<float> dt::json_container::float_at(std::string const& k) const noexcept
{ return _container.value_at<float>(k); }

std::optional<bool> dt::json_container::bool_at(std::string const& k) const noexcept
{ return _container.value_at<bool>(k); }

std::optional<std::string> dt::json_container::string_at(std::string const& k) const noexcept
{ return _container.value_at<std::string>(k); }

std::optional<dt::json_container> dt::json_container::container_at(std::string const& k) const noexcept {
  if (auto con{_container.container_at(k)}; con)
    return json_container(*con);

  return std::nullopt;
}

dt::json_t dt::json_container::type_at(std::size_t i) const noexcept
{ return _container.type_at(i); }

std::optional<int> dt::json_container::int_at(std::size_t i) const noexcept
{ return _container.value_at<int>(i); }

std::optional<float> dt::json_container::float_at(std::size_t i) const noexcept
{ return _container.value_at<float>(i); }

std::optional<bool> dt::json_container::bool_at(std::size_t i) const noexcept
{ return _container.value_at<bool>(i); }

std::optional<std::string> dt::json_container::string_at(std::size_t i) const noexcept
{ return _container.value_at<std::string>(i); }

std::optional<dt::json_container> dt::json_container::container_at(std::size_t i) const noexcept {
  if (auto con{_container.container_at(i)}; con)
    return json_container(*con);

  return std::nullopt;
}
