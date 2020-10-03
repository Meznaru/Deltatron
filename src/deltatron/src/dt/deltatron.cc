// deltatron.cc

#include <dt/deltatron.hh>

dt::deltatron::deltatron(int ac, char const** av, char const** ep)
: _config(ac, av, ep) {}

void dt::deltatron::run() const {

  _config.rootdir().load_directory("testdir1").load_directory("testdir2").load_file({ .name = "test.txt" });

}
