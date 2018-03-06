#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H

#include <memory>

namespace fictionalfiesta
{

class XmlDocumentImpl;

class XmlDocument
{
  private:

    /// Pointer to the document implementation.
    // We use PIMPL to avoid exposing the XML dependecies.
    std::unique_ptr<XmlDocumentImpl> _document;
};

}

#endif
