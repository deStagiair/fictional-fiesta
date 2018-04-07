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

    /// @brief Obtains a string representation of the class.
    /// @param indentLevel Indentation level.
    /// @return String representation of the class.
    virtual std::string str(unsigned int indentLevel) const = 0;

  protected:

    /// @brief Obtains a string representing a given level of indentation.
    /// @param indentLevel Level of indentation to stringify.
    /// @return String repesenting the indentation level.
    static std::string indent(unsigned int indentLevel);
};

/// @brief Prints the string representation to the output stream.
/// @param os Output stream where the descriptable will be written.
/// @param descriptable Instance to be stringified.
/// @return Modified output stream.
std::ostream& operator<<(std::ostream& os, const Descriptable& descriptable);

} // namespace fictionalfiesta

#endif
