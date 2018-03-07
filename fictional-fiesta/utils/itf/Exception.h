#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_EXCEPTION_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_EXCEPTION_H

#include <exception>

#include <string>

namespace fictionalfiesta
{

class Exception : public std::exception
{
  private:

    /// Message for logging purposes.
    std::string _logMessage;

  public:

    /// Constructor that takes the log message.
    /// @param logMessage message for logging purposes.
    explicit Exception(const std::string &logMessage);

    /// Gets an string identifying the exception.
    /// @return string identifying the exception.
    const char* what() const noexcept override;
};

} // namespace fictionalfiesta

#endif
