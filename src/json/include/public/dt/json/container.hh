// object.hh

#pragma once

#include <dt/json/container/value.hh>

#include <map>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

namespace dt {

class json_parser;

class json_container final {
public:
  using value_type     = std::variant<json_container, json_value>;
  using object_type    = std::map<std::string_view, value_type>;
  using array_type     = std::vector<value_type>;
  using container_type = std::variant<object_type, array_type>;

private:
  friend class ::dt::json_parser;

  std::string const& _id;
  json_value_t       _type;
  container_type     _value;

public:
  constexpr auto type() const noexcept { return _type; }

  json_value_t type_at(object_type::key_type v) const {
    auto const& obj_v = std::get<object_type>(_value);

    if (obj_v.contains(v)) {
      json_value_t t{};
      std::visit([&t](auto&& i) mutable { t = i.type(); }, obj_v.at(v));
      return t;
    }

    return json_value_t::Null;
  }

  json_container const& json_container_at(object_type::key_type v) const {
    return std::get<json_container>(std::get<object_type>(_value).at(v));
  }

  json_value::value_type json_value_at(object_type::key_type v, json_value_t type) const {
    auto const& obj_v = std::get<object_type>(_value);
    switch (type) {
    case json_value_t::String:
      return std::get<json_value>(obj_v.at(v)).string_value();
    case json_value_t::Integer:
      return std::get<json_value>(obj_v.at(v)).integer_value();
    case json_value_t::Float:
      return std::get<json_value>(obj_v.at(v)).float_value();
    case json_value_t::Bool:
      return std::get<json_value>(obj_v.at(v)).bool_value();
    default:
      return std::nullopt;
    }
  }

  json_value_t type_at(array_type::size_type idx) const {
    auto const& arr_v = std::get<array_type>(_value);

    if (idx < arr_v.size()) {
      json_value_t t{};
      std::visit([&t](auto&& i) mutable { t = i.type(); }, arr_v.at(idx));

      return t;
    }

    return json_value_t::Null;
  }

  json_container const& json_container_at(array_type::size_type idx) const {
    return std::get<json_container>(std::get<array_type>(_value).at(idx));
  }

  json_value::value_type json_value_at(array_type::size_type idx, json_value_t type) const {
    auto const& arr_v = std::get<array_type>(_value);
    switch (type) {
    case json_value_t::String:
      return std::get<json_value>(arr_v.at(idx)).string_value();
    case json_value_t::Integer:
      return std::get<json_value>(arr_v.at(idx)).integer_value();
    case json_value_t::Float:
      return std::get<json_value>(arr_v.at(idx)).float_value();
    case json_value_t::Bool:
      return std::get<json_value>(arr_v.at(idx)).bool_value();
    default:
      return std::nullopt;
    }
  }

private:
  json_container(std::string const& id, json_value_t type, container_type value)
  : _id(id),
    _type(type),
    _value(value) {}
};

}
