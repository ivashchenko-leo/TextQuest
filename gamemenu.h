#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>
#include <QtXml>
#include "xmlchapters.h"

namespace Ui {
class GameMenu;
}
class XmlChapters;

class GameMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();
    QString fileName;
    void setFileName(QString fileName);
    QString getFileName();
    void loadTree();

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
    QXmlSimpleReader reader;
    XmlChapters *handler;

private slots:
    void chapters();
    void loadMenu();
    void newGame();

};

#endif // GAMEMENU_H
