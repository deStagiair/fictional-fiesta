#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_SAVABLE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_SAVABLE_H

#include <experimental/filesystem>

#include <string>
#include <ostream>

namespace fictionalfiesta
{

class XmlNode;

/// @class XmlSavable
/// @brief Interface for all the classes that can be saved to XML.
class XmlSavable
{
  public:

    /// @brief Save the class contents into a XML node.
    /// @param node XML node where to save the XML contents.
    void save(XmlNode node) const;

    /// @brief Save the class contents into a file.
    /// @param filePath Path where the XML will be saved.
    void save(const std::experimental::filesystem::path& filePath) const;

    /// @brief Save the class contents into a file.
    /// @param stream Stream where the XML will be saved.
    void save(std::ostream& stream) const;

  private:

    /// @brief Save the class contents into a XML node.
    /// @param node XML node where to save the XML contents.
    virtual void doSave(XmlNode& node) const = 0;

    /// @brief Get the default main XML node name for the class.
    /// @return Default main XML node name.
    virtual std::string getDefaultXmlName() const = 0;
};

} // namespace fictionalfiesta

#endif
