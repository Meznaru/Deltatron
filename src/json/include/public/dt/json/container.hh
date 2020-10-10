// object.hh

#pragma once

#include <dt/json/container/value.hh>

#include <map>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

namespace dt {

class json;
class json_parser;

class json_container final {
public:
  using basic_type  = std::variant<json_container, json_value>;
  using object_type = std::map<std::string, basic_type>;
  using array_type  = std::vector<basic_type>;
  using value_type  = std::variant<object_type, array_type>;

private:
  friend class ::dt::json;
  friend class ::dt::json_parser;

  std::string const& _id;
  json_value_t       _type;
  value_type         _value;

public:
  constexpr auto type() const noexcept -> json_value_t       { return _type; }

  constexpr auto id()   const noexcept -> std::string const& { return _id;   }

  json_value_t type_at(object_type::key_type v) const {
    auto const& obj_v = std::get<object_type>(_value);

    if (obj_v.contains(v)) {
      json_value_t t{};
      std::visit([&t](auto&& i) mutable { t = i.type(); }, obj_v.at(v));
      return t;
    }

    return json_value_t::Null;
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

  json_container const& json_container_at(object_type::key_type v) const
  { return std::get<json_container>(std::get<object_type>(_value).at(v)); }

  json_container const& json_container_at(array_type::size_type idx) const
  { return std::get<json_container>(std::get<array_type>(_value).at(idx)); }

  json_value::value_type json_value_at(object_type::key_type v) const
  { return _get_json_value(std::get<json_value>(std::get<object_type>(_value).at(v))); }

  json_value::value_type json_value_at(array_type::size_type idx) const
  { return _get_json_value(std::get<json_value>(std::get<array_type>(_value).at(idx))); }

private:
  json_value::value_type _get_json_value(json_value const& v) const {
    switch (v.type()) {
    case json_value_t::String:
      return v.string_value();
    case json_value_t::Integer:
      return v.integer_value();
    case json_value_t::Float:
      return v.float_value();
    case json_value_t::Bool:
      return v.bool_value();
    default:
      return std::nullopt;
    }
  }

  json_container(std::string const& id, json_value_t type = json_value_t::Object, value_type value = object_type())
  : _id(id),
    _type(type),
    _value(value) {}
};

}
