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
    QDomNode getChapter(const int chapterNumber);
    int getChapter(QString sceneId);
    QDomNode getP(QDomNode scene, int pNumber);
    QDomNode getSceneElement(QDomNode scene, int pNumber);
    QDomNodeList getPList(QDomNode scene);
    QDomNodeList getChoiceList(QDomNode scene);
    QString getMenuImage();
    QString getMenuSound();
    QString getChapterIcon(QDomNode chapter);
    QString getFirstChapter();
    bool isPExist(QDomNode scene, int pNumber);
    bool isSceneExist(QDomNode chapter, int sceneNumber);
    bool isSceneExist(const QString id);
    bool isChapterExist(const int chapterNumber);
    bool isElementExist(QDomNode scene, int pNumber);
    QDomNodeList getChoicesList(QDomNode scene);
    void loadXml(QString fileName);
    QString getGameName();

private:
    QDomElement domElement;

};

#endif // XMLDOM_H
