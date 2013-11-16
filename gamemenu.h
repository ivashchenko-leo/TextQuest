#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>
#include <QtXml>
//#include "xmlchapters.h"
#include "xmldom.h"
#include <QMessageBox>

namespace Ui {
class GameMenu;
}
//class XmlChapters;
class XmlDom;

class GameMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();
    //void loadTree(QFile *file);
    void loadXml(QString fileName);

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

private:
    Ui::GameMenu *ui;
    XmlDom *xmlDoc;
    //QXmlSimpleReader reader;
    //QStack<QFile> filesStack;
    //void parseXml();

private slots:
    void chapters();
    void loadMenu();
    void newGame();
    //void getNewFile(QFile file);

};

#endif // GAMEMENU_H
