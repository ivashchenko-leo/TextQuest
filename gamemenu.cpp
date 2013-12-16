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
const QString GameMenu::JumpTag("jump");

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

    this->ui->pbBack->installEventFilter(new HoverFilter());
    this->ui->pbNewGame->installEventFilter(new HoverFilter());
    this->ui->pbChapters->installEventFilter(new HoverFilter());
    this->ui->pbLoad->installEventFilter(new HoverFilter());
}

void GameMenu::loadXml(QString fileName)
{
    this->xmlDoc->loadXml(fileName);
}

void GameMenu::prepare()
{
    if (Settings::instance()->getOption(Settings::FullScreen).toBool()) {
        this->showFullScreen();
    } else {
        this->setFixedSize(Settings::Width, Settings::Height);
    }

    char *fileName = this->xmlDoc->getMenuSound().toUtf8().data();

    if (BASS_Init(-1, 44100, BASS_DEVICE_DEFAULT, this->winId(), NULL)) {
        if (!this->xmlDoc->getMenuSound().isEmpty()) {
            MainWindow::stream = BASS_StreamCreateFile(FALSE, fileName, 0, 0, BASS_UNICODE);
            if (MainWindow::stream != 0) {
                BASS_SetVolume(Settings::instance()->getOption(Settings::Volume).toFloat()/100.0);
                BASS_ChannelPlay(MainWindow::stream, true);
            } else {
                qWarning() << "Error! Bass_StreamCreateFile code" << BASS_ErrorGetCode();
            }
        }
    } else {
        qWarning() << "Error! Bass_Init code " << BASS_ErrorGetCode();
    }

    QImage background(this->xmlDoc->getMenuImage());

    if (background.isNull()) {
        background = QImage(":/backgrounds/D:/Wallpaper/TextQuest/book tree.jpg");
    }

    QPalette palette = this->palette();
    QBrush brush(Qt::TexturePattern);

    background = background.scaled(this->size());
    brush.setTextureImage(background);
    palette.setBrush(QPalette::Background, brush);

    this->setPalette(palette);

}

GameMenu::~GameMenu()
{
    delete ui;
}

bool GameMenu::close()
{
    BASS_Free();
    return QDialog::close();
}

void GameMenu::newGame()
{
    GameWindow gameWindow(this, this->xmlDoc);
    this->hide();
    connect(&gameWindow, SIGNAL(destroyed()), this, SLOT(show()));
    gameWindow.start();
    gameWindow.exec();
}

void GameMenu::loadMenu()
{

}

void GameMenu::chapters()
{
//    QFile file(this->mainFile);
//    QXmlInputSource source(&file);

//    reader.setContentHandler(this->handler);
//    reader.parse(source);
}
