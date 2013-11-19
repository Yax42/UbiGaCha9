#ifndef	_UBIEXCEPTION_HH_
#define	_UBIEXCEPTION_HH_

#include <exception>
#include <string>
#include <sstream>

class UbiException : public std::exception
{
private:
  std::string _msg;

public:
  UbiException(const std::string &);
  virtual ~UbiException() throw() {}
  virtual const char *what() const throw();
};

#endif	/* _MY_EXCEPTION_HH_ */
