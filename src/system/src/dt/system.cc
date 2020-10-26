// system.cc

#include <dt/system.hh>
#include <dt/system_imp.hh>

#include <stdexcept>

static bool _was_init{false};

dt::system::system(int ac, char const** av, char const** ep)
: _system(([](bool& i = _was_init) mutable
    { if (i) throw std::runtime_error("calling system ctor twice"); i = true; }(),
  std::make_unique<system_imp>(ac, av, ep))) { }

dt::system::~system() noexcept {}

bool dt::system::cmdflag_passed(dt::flag_id id) const noexcept
{ return _system->cmdflag_passed(id); }

std::optional<std::string_view> dt::system::cmdflag_value(dt::flag_id id) const noexcept
{ return _system->cmdflag_value(id); }

bool dt::system::evar_defined(std::string_view var) const noexcept
{ return _system->evar_defined(var); }

std::optional<std::string_view> dt::system::evar_value(std::string_view var) const noexcept
{ return _system->evar_value(var); }

dt::directory dt::system::rootdir() const noexcept
{ return _system->rootdir(); }

dt::os_id dt::system::os() const noexcept
{ return _system->os(); }
