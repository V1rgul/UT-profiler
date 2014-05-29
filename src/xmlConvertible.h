#ifndef __XML_CONVERTIBLE__
#define __XML_CONVERTIBLE__

#include <QDomElement>

class XmlConvertible {
  public:
    virtual ~XmlConvertible () {}
    virtual QDomElement toXml () const = 0;
    virtual void fromXml (const QDomNode& n) = 0;
};

#endif
