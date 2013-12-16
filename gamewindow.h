#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QMenu>
#include "xmldom.h"
#include <QLabel>
#include "settings.h"
#include "mousefilter.h"
#include "choicefilter.h"
#include <QVBoxLayout>


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
    void setChapter();
    void setNewFile(QString fileName);
    QVBoxLayout *mainLayout;
    QLabel *currentLabel;
    bool choiceNotExist;
    void sendLeftClick();
    QColor textColor;
    QWidget *getWidgetOnCoord(QPoint coord);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::GameWindow *ui;
    QString pText;
    void showParagraph(QDomNode paragraph);
    void showChoices();
    void showImage(QDomNode image);
    void playSound(QDomNode sound);
    void clrscr();
    void jump(QDomNode jumpNode);
    QAction *backAct;
    QAction *skipAct;
    QAction *saveAct;
    QAction *loadAct;
    QAction *toggleColorAct;
    QAction *fullScreenAct;
    //QAction *settings;
    QAction *autoReadAct;
    QAction *changeInterfaceAct;
    QAction *menuAct;
    void createActions();
    void setResolution(bool fullScreen);


private slots:
    void showChars();
    void stuck();
    void skipText();
    void toggleFullScreen();
    void toggleColor();
    void choiceClicked();

};

#endif // GAMEWINDOW_H
