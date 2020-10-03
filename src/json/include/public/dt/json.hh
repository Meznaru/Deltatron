// json.hh

#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace dt {

class json_imp;

class json final {
  std::unique_ptr<json_imp> const _json;

public:
  json(std::string const& id, std::string_view const& data);

  ~json() noexcept;
};

}
