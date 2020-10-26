// container_imp.hh

#pragma once

#include <dt/json/container/value.hh>

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include <cstddef>

namespace dt {

class json_container_imp;

using json_type        = std::variant<json_container_imp, json_value>;
using json_object_type = std::map<std::string, json_type>;
using json_array_type  = std::vector<json_type>;

class json_parser;

class json_container_imp final {
public:
  friend class ::dt::json_parser;

  using value_t = std::variant<json_object_type, json_array_type>;

private:
  json_t  _type;
  value_t _value;

public:
  constexpr auto type() const noexcept -> json_t { return _type; }

  template <typename T>
  std::optional<T> value_at(std::string const& k) const noexcept {
    if (auto const* obj{_obj_has(k)}; obj)
      if (auto const* val{std::get_if<json_value>(&obj->at(k))}; val)
        return val->opt_val<T>();

    return std::nullopt;
  }

  constexpr json_t type_at(std::string const& k) const noexcept {
    if (auto const* obj{_obj_has(k)}; obj)
      return std::visit([](auto&& m) { return m.type(); }, obj->at(k));

    return json_t::Null;
  }

  constexpr json_container_imp const* container_at(std::string const& k) const noexcept {
    if (auto const* obj{_obj_has(k)}; obj)
      if (auto const* con{std::get_if<json_container_imp>(&obj->at(k))}; con)
        return con;

    return nullptr;
  }

  template <typename T>
  std::optional<T> value_at(std::size_t i) const noexcept {
    if (auto const* arr{_arr_has(i)}; arr)
      if (auto const* val{std::get_if<json_value>(&arr->at(i))}; val)
        return val->opt_val<T>();

    return std::nullopt;
  }

  constexpr json_t type_at(std::size_t i) const noexcept {
    if (auto const* arr{_arr_has(i)}; arr)
      return std::visit([](auto&& m) { return m.type(); }, arr->at(i));

    return json_t::Null;
  }

  constexpr json_container_imp const* container_at(std::size_t i) const noexcept {
    if (auto const* arr{_arr_has(i)}; arr)
      if (auto const* con{std::get_if<json_container_imp>(&arr->at(i))}; con)
        return con;

    return nullptr;
  }

private:
  constexpr json_array_type const* _arr_has(std::size_t i) const noexcept {
    if (auto const* arr{std::get_if<json_array_type>(&_value)}; arr && i < arr->size())
      return arr;

    return nullptr;
  }

  constexpr json_object_type const* _obj_has(std::string const& k) const noexcept {
    if (auto const* obj{std::get_if<json_object_type>(&_value)}; obj && obj->contains(k))
      return obj;

    return nullptr;
  }

  json_container_imp(json_t type, value_t value) noexcept
  : _type(type),
    _value(value) {}
}; // class json_container_imp

} // namespace dt
