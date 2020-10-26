// main.cc

#include <dt/deltatron.hh>

#include <iostream>

int main(int ac, char const** av, char const** ep) {
  try {
    dt::deltatron const deltatron(ac, av, ep);
    deltatron.run();

  } catch (dt::termflag_passed const& tf) {
    std::cerr << tf.msg << std::endl;

  } catch(std::runtime_error const& re) {
    std::cerr << "std::runtime_error: " << re.what() << std::endl;

  } catch (std::exception const& e) {
    std::cerr << "std::exception: " << e.what() << std::endl;

  } catch (char const* cstr) {
    std::cerr << "error: " << cstr << std::endl;

  } catch (...) {
    std::cerr << "error: unknown type caught in main" << std::endl;

  }
}
