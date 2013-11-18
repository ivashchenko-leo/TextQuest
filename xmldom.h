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
    QDomNode getScene(const QString id);
    QDomNode getScene(QDomNode chapter, int sceneNumber);
    QDomNode getChapter(const QString chapterName);
    QDomNode getChapter(const int chapterNumber);
    QDomNode getP(QDomNode scene, int pNumber);
    QDomNodeList getPList(QDomNode scene);
    QDomNodeList getChoiceList(QDomNode scene);
    QString getMenuImage();
    QString getMenuSound();
    QString getChapterIcon(QDomNode chapter);
    QString getSceneImage(QDomNode scene);
    QString getSceneSound(QDomNode scene);
    QString getFirstChapter();
    bool isPExist(QDomNode scene, int pNumber);
    bool isSceneExist(QDomNode chapter, int sceneNumber);
    bool isSceneExist(const QString id);
    bool isChapterExist(const QString chapterName);
    bool isChapterExist(const int chapterNumber);

private:
    QDomElement domElement;
    QDomNodeList chapterList;

};

#endif // XMLDOM_H
