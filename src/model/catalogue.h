#ifndef __CATALOGUE__
#define __CATALOGUE__

class Catalogue : public XmlConvertible {
  public:
    static Catalogue* instance ();
    static const QString Catalogue::XML_NODE_NAME;

    void ajouterUv (const UV& uv);
    void supprimerUv (const UV& uv);
    void editerUv (const UV& uv);
    bool existe (QString& tag);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QMap<QString, UV> uvs () { return _uvs; }
  private:
    Catalogue () {}
    static Catalogue* _instance;
    QMap<QString, UV> _uvs;
};

#endif
