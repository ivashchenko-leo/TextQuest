#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

namespace Ui {
class GameMenu;
}

class GameMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();
    QString fileName;
    void setFileName(QString fileName);
    QString getFileName();

private:
    Ui::GameMenu *ui;

private slots:
    void chapters();
    void loadMenu();
    void newGame();

};

#endif // GAMEMENU_H
