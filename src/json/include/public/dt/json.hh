// json.hh

#pragma once

#include <dt/json/container.hh>

#include <memory>
#include <string>
#include <string_view>

namespace dt {

class json_imp;

class json final {
  std::unique_ptr<json_imp> _json;

public:
  json(std::string id, std::string_view data);

  ~json() noexcept;

  json_container root() const noexcept;
};

}
