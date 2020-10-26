// deltatron.cc

#include <dt/deltatron.hh>

#include <dt/json.hh>

dt::deltatron::deltatron(int ac, char const** av, char const** ep)
: _system(ac, av, ep) {}

void dt::deltatron::run() const {

  json test("test.json", "{ \"key\": 12 }");

}
