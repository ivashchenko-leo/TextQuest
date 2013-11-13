#ifndef XMLCHAPTERS_H
#define XMLCHAPTERS_H

#include <QtXml>

class XmlChapters : public QXmlDefaultHandler
{
public:
    XmlChapters();
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);
    bool characters(const QString &ch);
    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName);
    bool fatalError(const QXmlParseException &exception);

private:
    QString data;
};

#endif // XMLCHAPTERS_H
