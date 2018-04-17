#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XMLABLE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XMLABLE_H

#include <string>

#include <experimental/filesystem>

namespace fictionalfiesta
{

class XmlNode;

/// @class Xmlable
/// @brief Interface for all the classes that can be loaded/saved from/to XML.
class Xmlable
{
  public:

    /// @brief Save the class contents into a XML node.
    /// @param node XML node where to save the XML contents.
    void save(XmlNode node) const;

  private:

    /// @brief Load the class contents from a XML node.
    /// @param node XML node from were to load the class contents.
    virtual void doLoad(const XmlNode& node) = 0;

    /// @brief Save the class contents into a XML node.
    /// @param node XML node where to save the XML contents.
    virtual void doSave(XmlNode& node) const = 0;
};

} // namespace fictionalfiesta

#endif