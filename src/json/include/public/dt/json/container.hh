// object.hh

#pragma once

#include <dt/json/container/value.hh>

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace dt {

class json_container;

using json_type = std::variant<json_container, json_value>;

using json_object_type = std::map<std::string, json_type>;

using json_array_type = std::vector<json_type>;



class json_parser;

class json_container final {
public:
  using value_type = std::variant<json_object_type, json_array_type>;

private:
  std::string const& _id;
  json_value_t       _type;
  value_type         _value;

  friend class ::dt::json_parser;

public:
  constexpr auto type() const noexcept -> json_value_t       { return _type; }
  constexpr auto id()   const noexcept -> std::string const& { return _id;   }

  constexpr json_object_type const& obj() const noexcept { return std::get<json_object_type>(_value); }
  constexpr json_array_type  const& arr() const noexcept { return std::get<json_array_type>(_value);  }

private:
  json_container(std::string const& id, json_value_t type, value_type value) noexcept
  : _id(id),
    _type(type),
    _value(value) {}
}; // class json_container

} // namespace dt
