// main.cc

#include <dt/deltatron.hh>

#include <iostream>

int main(int ac, char const** av, char const** ep) {
  try {

    dt::deltatron deltatron(ac, av, ep);

    deltatron.run();

  } catch (dt::termflag_passed const& tf) {
    std::cerr << tf.msg << std::endl;

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;

  } catch (...) {
    std::cerr << "unknown type caught in main" << std::endl;

  }
}
