// type.hh

#pragma once

namespace dt {

enum class json_t {
  Null, Bool, String, Float, Integer,

  Object, Array,

  LBrace = '{', LBrack = '[',
  RBrace = '}', RBrack = ']',
  Comma  = ',', Colon  = ':'
};

}
