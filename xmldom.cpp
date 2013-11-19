#include "xmldom.h"

//P = Paragraph

XmlDom::XmlDom(QObject *parent) :
    QObject(parent)
{
}

void XmlDom::setGameElement(const QDomElement element)
{
    this->domElement = element;
}

QDomNodeList XmlDom::getChaptersList()
{
    return this->domElement.elementsByTagName(GameMenu::ChapterTag);
}

QDomNodeList XmlDom::getSceneList(const QString chapterName)
{
    QDomNodeList empty;
    for (int i = 0; i < this->domElement.elementsByTagName(GameMenu::ChapterTag).size(); i++) {
        if (this->domElement.elementsByTagName(GameMenu::ChapterTag).at(i).toElement().attribute("name") == chapterName)
            return this->domElement.elementsByTagName(GameMenu::ChapterTag).at(i).toElement().elementsByTagName(GameMenu::SceneTag);
    }
    return empty;
}

QDomNode XmlDom::getScene(const QString id)
{
    QDomNodeList sceneList;
    QDomNode empty;
    for (int i = 0; i < this->domElement.elementsByTagName(GameMenu::ChapterTag).size(); i++) {
        sceneList = this->domElement.elementsByTagName(GameMenu::ChapterTag).at(i).toElement().elementsByTagName(GameMenu::SceneTag);
        for (int j = 0; j < sceneList.size(); j++) {
            if (sceneList.at(j).toElement().attribute("id") == id) {
                return sceneList.at(j);
            }
        }
    }
    return empty;
}

QDomNode XmlDom::getScene(QDomNode chapter, int sceneNumber)
{
    QDomNodeList sceneList;

    sceneList = chapter.toElement().elementsByTagName(GameMenu::SceneTag);
    return sceneList.at(sceneNumber);
}

bool XmlDom::isSceneExist(const QString id)
{
    QDomNodeList sceneList;

    for (int i = 0; i < this->domElement.elementsByTagName(GameMenu::ChapterTag).size(); i++) {
        sceneList = this->domElement.elementsByTagName(GameMenu::ChapterTag).at(i).toElement().elementsByTagName(GameMenu::SceneTag);
        for (int j = 0; j < sceneList.size(); j++) {
            if (sceneList.at(j).toElement().attribute("id") == id) {
                return true;
            }
        }
    }
    return false;
}

bool XmlDom::isSceneExist(QDomNode chapter, int sceneNumber)
{
    QDomNode scene;
    scene = this->getScene(chapter, sceneNumber);
    if (scene.isNull())
        return false;
    else
        return true;
}

bool XmlDom::isChapterExist(const int chapterNumber)
{
    if (this->getChapter(chapterNumber).isNull())
        return false;
    else
        return true;
}

QDomNode XmlDom::getChapter(const int chapterNumber)
{
    return this->domElement.elementsByTagName(GameMenu::ChapterTag).at(chapterNumber);
}

QString XmlDom::getMenuImage()
{
    QDomNodeList list;
    list = this->domElement.elementsByTagName(GameMenu::MenuImgTag);

    return list.at(list.size()).toElement().text();
}

QString XmlDom::getMenuSound()
{
    QDomNodeList list;
    list = this->domElement.elementsByTagName(GameMenu::MenuSoundTag);

    return list.at(list.size()).toElement().text();
}

QString XmlDom::getChapterIcon(QDomNode chapter)
{
    QDomNodeList list;
    list = chapter.toElement().elementsByTagName(GameMenu::IconTag);

    return list.at(list.size()).toElement().text();
}

QDomNodeList XmlDom::getPList(QDomNode scene)
{
    return scene.toElement().elementsByTagName(GameMenu::PTag);
}

QDomNodeList XmlDom::getChoiceList(QDomNode scene)
{
    return scene.toElement().elementsByTagName(GameMenu::ChoiceTag);
}

QString XmlDom::getFirstChapter()
{
    return this->domElement.elementsByTagName(GameMenu::ChapterTag).at(0).toElement().attribute("name");
}

bool XmlDom::isPExist(QDomNode scene, int pNumber)
{
    QDomNodeList list;
    list = this->getPList(scene);
    if (pNumber >= list.size() || pNumber < 0) {
        return false;
    }
    return true;
}

QDomNode XmlDom::getP(QDomNode scene, int pNumber)
{
    QDomNodeList list;
    list = this->getPList(scene);

    return list.at(pNumber);
}

QDomNode XmlDom::getSceneElement(QDomNode scene, int pNumber)
{
    QDomNodeList list;
    list = scene.toElement().childNodes();

    return list.at(pNumber);
}

bool XmlDom::isElementExist(QDomNode scene, int pNumber)
{
    if (scene.toElement().childNodes().size() <= pNumber || pNumber < 0) {
        return false;
    }
    return true;
}

int XmlDom::getChapter(QString sceneId)
{
    QDomNodeList sceneList;
    for (int i = 0; i < this->domElement.elementsByTagName(GameMenu::ChapterTag).size(); i++) {
        sceneList = this->domElement.elementsByTagName(GameMenu::ChapterTag).at(i).toElement().elementsByTagName(GameMenu::SceneTag);
        for (int j = 0; j < sceneList.size(); j++) {
            if (sceneList.at(j).toElement().attribute("id") == sceneId) {
                return i;
            }
        }
    }
    return -1;
}














