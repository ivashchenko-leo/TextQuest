#include "gamemenu.h"
#include "ui_gamemenu.h"

const QString GameMenu::GameTag("game");
const QString GameMenu::ChapterTag("chapter");
const QString GameMenu::SceneTag("scene");
const QString GameMenu::ImageTag("image");
const QString GameMenu::SoundTag("sound");
const QString GameMenu::IconTag("icon");
const QString GameMenu::PTag("p");
const QString GameMenu::FileTag("file");
const QString GameMenu::ChoiceTag("choice");
const QString GameMenu::MenuImgTag("menuimg");
const QString GameMenu::MenuSoundTag("menusound");

GameMenu::GameMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMenu),
    handler(new XmlChapters())
{
    ui->setupUi(this);

    connect(ui->pbBack, SIGNAL(clicked()), SLOT(close()));
    connect(ui->pbNewGame, SIGNAL(clicked()), SLOT(newGame()));
    connect(ui->pbChapters, SIGNAL(clicked()), SLOT(chapters()));
    connect(ui->pbLoad, SIGNAL(clicked()), SLOT(loadMenu()));
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

void GameMenu::loadTree()
{
    QFile file(this->fileName);
    QXmlInputSource source(&file);

    if (this->fileName.isEmpty()) {
        qDebug() << "property fileName is empty";
    } else {
        this->reader.setContentHandler(this->handler);
        this->reader.parse(source);
    }
}

void GameMenu::chapters()
{
    QFile file(this->fileName);
    QXmlInputSource source(&file);

    reader.setContentHandler(this->handler);
    reader.parse(source);
}
