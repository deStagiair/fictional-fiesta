#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_FACTORY_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_FACTORY_H

#include <memory>

namespace fictionalfiesta
{

class Source;
class XmlNode;

/// @brief Factory class to create sources.
class SourceFactory
{
  public:

    /// @brief Creates a source from an XmlNode.
    /// @param node XML node with the source contents.
    /// @return owner pointer to the created source.
    static std::unique_ptr<Source> createSource(const XmlNode& node);
};

}

#endif
