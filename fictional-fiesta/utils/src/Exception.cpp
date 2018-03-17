/// Implementation of the Exception class.

#include "fictional-fiesta/utils/itf/Exception.h"

namespace fictionalfiesta
{

Exception::Exception(const std::string& logMessage):
  _logMessage(logMessage)
{
}

const char* Exception::what() const noexcept
{
  return _logMessage.c_str();
}

} // namespace fictionalfiesta
