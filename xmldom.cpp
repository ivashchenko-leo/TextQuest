#include "xmldom.h"

XmlDom::XmlDom(QObject *parent) :
    QObject(parent)
{
}

void XmlDom::setGameElement(const QDomElement element)
{
    this->domElement = element;
    this->chapterList = element.elementsByTagName(GameMenu::ChapterTag);
}

QDomNodeList XmlDom::getChaptersList()
{
    return this->chapterList;
}

QDomNodeList XmlDom::getSceneList(const QString chapterName)
{
    QDomNodeList empty;
    for (int i = 0; i < this->chapterList.size(); i++) {
        if (this->chapterList.at(i).toElement().attribute("name") == chapterName)
            return this->chapterList.at(i).toElement().elementsByTagName(GameMenu::SceneTag);
    }
    return empty;
}

QDomNode XmlDom::getNextChapter(QDomNode chapter)
{
    return this->getNextChapter(chapter.toElement().attribute("name"));
}

QDomNode XmlDom::getNextChapter(const QString chapterName)
{
    QDomNode empty;
    for (int i = 0; i < this->chapterList.size(); i++) {
        if (this->chapterList.at(i).toElement().attribute("name") == chapterName) {
            if (i+1 <= this->chapterList.size())
                return this->chapterList.at(i+1);
        }
    }
    return empty;
}

QDomNode XmlDom::getScene(const QString id)
{
    QDomNode empty;
    QDomNodeList sceneList;

    for (int i = 0; i < this->chapterList.size(); i++) {
        sceneList = this->chapterList.at(i).toElement().elementsByTagName(GameMenu::SceneTag);
        for (int j = 0; j < sceneList.size(); j++) {
            if (sceneList.at(j).toElement().attribute("id") == id) {
                return sceneList.at(j);
            }
        }
    }
    return empty;
}

QDomNode XmlDom::getNextScene(const QString id)
{
    QDomNode empty;
    QDomNodeList sceneList;

    for (int i = 0; i < this->chapterList.size(); i++) {
        sceneList = this->chapterList.at(i).toElement().elementsByTagName(GameMenu::SceneTag);
        for (int j = 0; j < sceneList.size(); j++) {
            if (sceneList.at(j).toElement().attribute("id") == id) {
                if (j+1 <= sceneList.size())
                    return sceneList.at(j+1);
            }
        }
    }
    return empty;
}

QDomNode XmlDom::getNextScene(QDomNode scene)
{
    return this->getNextScene(scene.toElement().attribute("id"));
}

QDomNode XmlDom::getChapter(const QString chapterName)
{
    QDomNode empty;
    for (int i = 0; i < this->chapterList.size(); i++) {
        if (this->chapterList.at(i).toElement().attribute("name") == chapterName) {
            return this->chapterList.at(i);
        }
    }
    return empty;
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

QString XmlDom::getSceneImage(QDomNode scene)
{
    QDomNodeList list;
    list = scene.toElement().elementsByTagName(GameMenu::ImageTag);

    return list.at(list.size()).toElement().text();
}

QString XmlDom::getSceneSound(QDomNode scene)
{
    QDomNodeList list;
    list = scene.toElement().elementsByTagName(GameMenu::SoundTag);

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










