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
    xmlDoc(new XmlDom())
{
    ui->setupUi(this);

    connect(ui->pbBack, SIGNAL(clicked()), SLOT(close()));
    connect(ui->pbNewGame, SIGNAL(clicked()), SLOT(newGame()));
    connect(ui->pbChapters, SIGNAL(clicked()), SLOT(chapters()));
    connect(ui->pbLoad, SIGNAL(clicked()), SLOT(loadMenu()));
    //connect(this->handler, SIGNAL(newFile(QFile)), SLOT(getNewFile(QFile)));
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::newGame()
{

}

void GameMenu::loadMenu()
{

}
/*
void GameMenu::loadTree(QFile *file)
{
    this->parseXml(file);
}

void GameMenu::loadTree()
{
    QFile file(this->mainFile);
    this->parseXml(&file);
}

void GameMenu::parseXml(QFile *file)
{
    QXmlInputSource source(file);

    if (this->mainFile.isEmpty()) {
        qDebug() << "GameMenu: property fileName is empty";
    } else {
        this->reader.setContentHandler(this->handler);
        this->reader.parse(source);
    }
}*/
void GameMenu::loadXml(QString fileName)
{
    QDomDocument domDoc;

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        if (domDoc.setContent(&file)) {
            QDomElement domElement = domDoc.documentElement();
            if (domElement.tagName() != GameMenu::GameTag) {
                QMessageBox::critical(this, tr("Erorr!"), tr("This file is not TextQuest game xml file."));
            } else {
                this->setToolTip(domElement.attribute("name"));
                qDebug() << domElement.attribute("name");
            }
            this->xmlDoc->setGameElement(domElement);
        }
    }
}

//void GameMenu::getNewFile(QFile file)
//{
//    if (!this->filesStack.contains(file)) {
//       this->filesStack.push(file);
//    }
//}

void GameMenu::chapters()
{
//    QFile file(this->mainFile);
//    QXmlInputSource source(&file);

//    reader.setContentHandler(this->handler);
//    reader.parse(source);
}
