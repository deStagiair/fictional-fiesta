#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_DESCRIPTABLE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_DESCRIPTABLE_H

#include <string>

namespace fictionalfiesta
{

/// @class Descriptable
/// @brief Base class for all the classes that can obtain an string description.
class Descriptable
{
  public:

    /// @brief Obtains an string representation of the class.
    /// @param indentLevel Indentation level.
    virtual std::string str(unsigned int indentLevel) const = 0;

  protected:

    static std::string indent(unsigned int indentLevel);
};

} // namespace fictionalfiesta

#endif
