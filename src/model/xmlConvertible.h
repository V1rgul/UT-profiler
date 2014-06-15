#ifndef __XML_CONVERTIBLE__
#define __XML_CONVERTIBLE__

#include <QDomElement>

class XmlConvertible {
  public:
    virtual ~XmlConvertible () {}
    /**
     * @brief Convertit l'objet au format XML
     * @return L'élément XML correspondant
     */
    virtual QDomElement toXml () const = 0;

    /**
     * @brief Définit l'objet à partir d'un élément XML
     */
    virtual void fromXml (const QDomNode& n) = 0;
};

#endif
