// token_stream.cc

#include <dt/json/token/token_stream.hh>
#include <dt/json/token/stream_lexer.hh>
#include <dt/json/token/verify_token_stream.hh>

#include <iostream>

dt::token_stream_t
dt::generate_token_stream(std::string_view const& id, std::string_view const& data) {
  dt::token_stream_t ts{};

  for (dt::stream_lexer lexer(id, data); !lexer.done(); ++lexer)
    lexer.append_token(ts);

  verify_token_stream(id, ts);

  return ts;
}
