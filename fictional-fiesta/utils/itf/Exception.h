#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_EXCEPTION_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_EXCEPTION_H

#include <exception>

#include <string>

namespace fictionalfiesta
{

/// @class Exception
/// @brief Class to represent a general exception in the project.
class Exception : public std::exception
{
  private:

    /// Message for logging purposes.
    std::string _logMessage;

  public:

    /// @brief Constructor that takes the log message.
    /// @param logMessage message for logging purposes.
    explicit Exception(const std::string &logMessage);

    /// @brief Gets an string identifying the exception.
    /// @return string identifying the exception.
    const char* what() const noexcept override;
};

} // namespace fictionalfiesta

#endif
