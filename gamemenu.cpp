#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMenu)
{
    ui->setupUi(this);

    connect(ui->pbBack, SIGNAL(clicked()), SLOT(close());
    connect(ui->pbNewGame, SIGNAL(clicked()), SLOT(newGame());
    connect(ui->pbChapters, SIGNAL(clicked()), SLOT(chapters());
    connect(ui->pbLoad, SIGNAL(clicked()), SLOT(loadMenu());
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::setFileName(QString fileName)
{
    this->fileName = fileName;
}

QString GameMenu::getFileName()
{
    return this->fileName;
}

void GameMenu::newGame()
{

}

void GameMenu::loadMenu()
{

}

void GameMenu::chapters()
{

}
