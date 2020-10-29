// main.cc

#include <dt/deltatron.hh>

#include <exception>
#include <iostream>
#include <stdexcept>

int main(int ac, char const** av, char const** ep) {
  try {
    dt::deltatron const deltatron(ac, av, ep);
    deltatron.run();

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;

  } catch (...) {
    std::cerr << "unknown type caught by main" << std::endl;

  }
}
