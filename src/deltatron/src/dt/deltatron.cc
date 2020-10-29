// deltatron.cc

#include <dt/deltatron.hh>

#include <dt/json.hh>

#include <iostream>

dt::deltatron::deltatron(int ac, char const** av, char const** ep)
: _system(ac, av, ep) {}

void dt::deltatron::run() const {
  auto engine_name = dt::json("test_1.json", _system.root_dir().fload("test_1.json").value().data())
    .root().container_at("gpu_config").value().string_at("engine_name").value();

  auto number_2    = dt::json("test_1.json", _system.root_dir().fload("test_1.json").value().data())
    .root().container_at("some_array").value().int_at(1).value();

  std::cout << "\"engine_name\" == " << engine_name << std::endl;
  std::cout << "number_2 == "        << number_2 << std::endl;
}
