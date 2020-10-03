// json.cc

#include <dt/json.hh>
#include <dt/json_imp.hh>

dt::json::json(std::string const& id, std::string_view const& data)
: _json(std::make_unique<json_imp>(id, data)) {}

dt::json::~json() noexcept {}
