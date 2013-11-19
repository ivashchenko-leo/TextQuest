﻿#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "xmldom.h"
#include <QPushButton>
#include "settings.h"
#include "mousefilter.h"

namespace Ui {
class GameWindow;
}

class XmlDom;

class GameWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameWindow(QWidget *parent = 0, XmlDom *xmlDoc = 0);
    ~GameWindow();
    void setScene(QDomNode scene);
    void chooseAction(QDomNode node);
    void start();
    QTimer *pTimer;
    int tCount;
    int cCount;
    QString sceneId;
    void finishParagraph();
    XmlDom *xmlDoc;
    void setScene();
    QDomNode scene;
    int chapter;
    bool choiceNotExist;
    void setChapter();

protected:
    //void mousePressEvent(QMouseEvent *mouse);

private:
    Ui::GameWindow *ui;
    QString pText;
    void showParagraph(QDomNode paragraph);
    void showChoices();
    void showImage(QDomNode image);
    void playSound(QDomNode sound);
    void sendLeftClick();

private slots:
    void showChars();

};

#endif // GAMEWINDOW_H
