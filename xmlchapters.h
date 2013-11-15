#ifndef XMLCHAPTERS_H
#define XMLCHAPTERS_H

#include <QtXml>
#include "chaptersdialog.h"
#include "gamemenu.h"
#include <QMessageBox>

class XmlChapters : public QXmlDefaultHandler
{
public:
    XmlChapters();
    bool startElement(const QString &,
                      const QString &,
                      const QString &qName,
                      const QXmlAttributes &atts);
    bool characters(const QString &ch);
    bool endElement(const QString &,
                    const QString &,
                    const QString &qName);
    bool fatalError(const QXmlParseException &exception);
    QString getGameName();

    QString gameName;
    QMultiMap<QString, QString> gameTree;
    QMap<QString, QString> scenesImg;
    QMap<QString, QString> chaptersIcon;
    QString currentChapter;
    QString currentScene;

private:
   QString tagValue;

};

#endif // XMLCHAPTERS_H
