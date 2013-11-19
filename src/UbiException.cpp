#include "UbiException.hh"

UbiException::UbiException(const std::string & msg)
  : _msg(msg)
{
}

const char *UbiException::what() const throw()
{
  return (this->_msg.c_str());
}
