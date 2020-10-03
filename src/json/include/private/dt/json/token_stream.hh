// stream.hh

#include <dt/json/token_stream/token.hh>

namespace dt {

token_stream_t
manifest_token_stream(std::string_view const& id, std::string_view const& data);

}
