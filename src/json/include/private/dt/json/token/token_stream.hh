// stream.hh

#include <dt/json/token.hh>

namespace dt {

token_stream_t
create_token_stream(std::string_view const& id, std::string_view const& data);

}
