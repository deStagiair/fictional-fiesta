#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H

#include <libxml/tree.h>

namespace fictionalfiesta
{

class XmlNode
{
  private:

    /// Pointer to the internal XML node from libXml.
    xmlNodePtr _node;

  public:

    /// @brief Constructor from the pointer.
    ///
    /// @param node libXmlNodePointer
    explicit XmlNode(const xmlNodePtr &node);

};

}

#endif
