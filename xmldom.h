#ifndef XMLDOM_H
#define XMLDOM_H

#include <QObject>
#include <QtXml>
#include "gamemenu.h"
#include <QDomNodeList>

class XmlDom : public QObject
{
    Q_OBJECT
public:
    explicit XmlDom(QObject *parent = 0);
    QDomNodeList getChaptersList();
    void setGameElement(const QDomElement element);
    QDomNodeList getSceneList(const QString chapterName);
    QDomNode getNextChapter(QDomNode chapter);
    QDomNode getNextChapter(const QString chapterName);
    QDomNode getScene(const QString id);
    QDomNode getNextScene(const QString id);
    QDomNode getNextScene(QDomNode scene);
    QDomNode getChapter(const QString chapterName);
    QString getMenuImage();
    QString getMenuSound();
    QString getChapterIcon(QDomNode chapter);
    QString getSceneImage(QDomNode scene);
    QString getSceneSound(QDomNode scene);
    QDomNodeList getPList(QDomNode scene);
    QDomNodeList getChoiceList(QDomNode scene);

private:
    QDomElement domElement;
    QDomNodeList chapterList;

};

#endif // XMLDOM_H
