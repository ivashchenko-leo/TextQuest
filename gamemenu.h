﻿#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>
#include <QtXml>
#include "xmldom.h"
#include <QMessageBox>
#include "gamewindow.h"

namespace Ui {
class GameMenu;
}

class XmlDom;

class GameMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();
    void loadXml(QString fileName);
    void prepare();

    const static QString GameTag;
    const static QString ChapterTag;
    const static QString SceneTag;
    const static QString ImageTag;
    const static QString SoundTag;
    const static QString IconTag;
    const static QString PTag;
    const static QString FileTag;
    const static QString ChoiceTag;
    const static QString MenuImgTag;
    const static QString MenuSoundTag;
    const static QString JumpTag;

    XmlDom *xmlDoc;

private:
    Ui::GameMenu *ui;

private slots:
    void chapters();
    void loadMenu();
    void newGame();
    bool close();

};

#endif // GAMEMENU_H
