// json.hh

#pragma once

#include <dt/json/container.hh>
#include <dt/json/error.hh>

#include <memory>
#include <string>

namespace dt {

class json_imp;

class json final {
  std::unique_ptr<json_imp> _json;

public:
  json(std::string const& id, std::string const& data);

  ~json() noexcept;

  json_container root() const noexcept;
};

}
