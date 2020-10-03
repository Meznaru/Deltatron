// token_stream.cc

#include <dt/json/token_stream.hh>
#include <dt/json/token_stream/stream_lexer.hh>
#include <dt/json/token_stream/verify_stream.hh>

#include <iostream>

void print_token_stream(dt::token_stream_t const& ts) {
  for (auto const& t : ts) {
    auto const type = t.type();
    switch (type) {
    case dt::token_id::Comma:  [[fallthrough]];
    case dt::token_id::Colon:  [[fallthrough]];
    case dt::token_id::LBrace: [[fallthrough]];
    case dt::token_id::RBrace: [[fallthrough]];
    case dt::token_id::LBrack: [[fallthrough]];
    case dt::token_id::RBrack:
      std::cout << type << ' ';
      break;
    case dt::token_id::Integer:
      std::cout << t.int_value() << ' ';
      break;
    case dt::token_id::Float:
      std::cout << t.float_value() << ' ';
      break;
    case dt::token_id::String:
      std::cout << t.string_value() << ' ';
      break;
    case dt::token_id::Bool:
      std::cout << t.bool_value() << ' ';
      break;
    case dt::token_id::Null:
      std::cout << "null" << ' ';
    }
  }

  endl(std::cout);
}

dt::token_stream_t
dt::manifest_token_stream(std::string_view const& id, std::string_view const& data) {
  dt::token_stream_t ts{};

  for (dt::stream_lexer lexer(id, data); !lexer.done(); ++lexer)
    lexer.append_token(ts);

  print_token_stream(ts);

  return ts;
}
