#ifndef GAMEWINDOW_H
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
    void showChoices();
    void showParagraph(QDomNode paragraph);
    void start();
    QTimer *pTimer;
    int pCount;
    int cCount;
    int sCount;
    QString pText;
    void finishParagraph();
    XmlDom *xmlDoc;
    void setScene();
    QDomNode scene;
    int chapter;

protected:
    //void mousePressEvent(QMouseEvent *mouse);

private:
    Ui::GameWindow *ui;

private slots:
    void showChars();

};

#endif // GAMEWINDOW_H
