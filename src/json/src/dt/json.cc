// json.cc

#include <dt/json.hh>

#include <dt/json/lexer.hh>
#include <dt/json/verify_stream.hh>
#include <dt/json/parser.hh>

dt::json_object_type dt::json::_parse_stream(std::string_view data) const {
  json_stream_t ts{};

  for (json_lexer lex(_id, data); !lex.done(); ++lex)
    lex.append_token(ts);

  verify_stream(_id, ts);

  return json_parser(_id, ts).create_root_object();
}
