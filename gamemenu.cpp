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
    xmlDoc(new XmlDom()),
    ui(new Ui::GameMenu)
{
    ui->setupUi(this);

    connect(ui->pbBack, SIGNAL(clicked()), SLOT(close()));
    connect(ui->pbNewGame, SIGNAL(clicked()), SLOT(newGame()));
    connect(ui->pbChapters, SIGNAL(clicked()), SLOT(chapters()));
    connect(ui->pbLoad, SIGNAL(clicked()), SLOT(loadMenu()));

    if (Settings::instance()->getOption("FullScreen").toBool()) {
        this->showFullScreen();
    } else {
        this->setFixedSize(Settings::Width, Settings::Height);
    }
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::newGame()
{
    GameWindow gameWindow(this, this->xmlDoc);
    //this->hide();
    gameWindow.start();
    gameWindow.exec();
}

void GameMenu::loadMenu()
{

}

void GameMenu::loadXml(QString fileName)
{
    this->xmlDoc->loadXml(fileName);
    this->setToolTip(this->xmlDoc->getGameName());
}

void GameMenu::chapters()
{
//    QFile file(this->mainFile);
//    QXmlInputSource source(&file);

//    reader.setContentHandler(this->handler);
//    reader.parse(source);
}
