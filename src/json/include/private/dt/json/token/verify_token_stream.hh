// check_stream.hh

#pragma once

#include <dt/json/token.hh>

#include <string_view>

namespace dt {

void verify_token_stream(std::string_view const id, token_stream_t const& ts);

}
