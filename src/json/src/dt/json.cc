// json.cc

#include <dt/json.hh>

#include <dt/json/lexer.hh>
#include <dt/json/parser.hh>

dt::json_container dt::json::_parse_data(std::string_view data) {
  json_value::stream_type ts{};

  for (json_lexer lex{_id, data}; !lex.done(); ++lex)
    lex.append_token(ts);

  json_parser par(_id, ts);
  return par.create_container_tree();
}
