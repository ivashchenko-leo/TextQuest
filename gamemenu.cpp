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

    this->ui->pbBack->installEventFilter(new HoverFilter(this->ui->pbBack));
    this->ui->pbNewGame->installEventFilter(new HoverFilter(this->ui->pbNewGame));
    this->ui->pbChapters->installEventFilter(new HoverFilter(this->ui->pbChapters));
    this->ui->pbLoad->installEventFilter(new HoverFilter(this->ui->pbLoad));

    this->continueButton.setParent(this);
    this->continueButton.setText(tr("Продолжить"));
    this->continueButton.setFlat(true);
    this->continueButton.setPalette(this->ui->pbBack->palette());
    this->continueButton.installEventFilter(new HoverFilter(&this->continueButton));
    connect(&this->continueButton, SIGNAL(clicked()), this, SLOT(startPlay()));
    this->ui->splitter->addWidget(&this->continueButton);
    this->hideContinueButton();
}

void GameMenu::loadXml(QString fileName)
{
    this->xmlDoc->loadXml(fileName);
}

void GameMenu::setBackgroundImage(QImage background)
{
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

void GameMenu::playSound(char *fileName)
{
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
}

void GameMenu::prepare()
{
    if (Settings::instance()->getOption(Settings::FullScreen).toBool()) {
        this->showFullScreen();
    } else {
        this->setFixedSize(Settings::Width, Settings::Height);
    }

    this->playSound(this->xmlDoc->getMenuSound().toUtf8().data());

    this->setBackgroundImage(QImage(this->xmlDoc->getMenuImage()));

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

void GameMenu::hideContinueButton()
{
    this->continueButton.hide();
}

void GameMenu::startPlay()
{
    GameWindow gameWindow(this, this->xmlDoc);

    this->hide();
    this->hideContinueButton();

    connect(&gameWindow, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&gameWindow, SIGNAL(returnToMenu(QString)), this, SLOT(setScene(QString)));

    gameWindow.setScene(this->sceneId);
    gameWindow.start();
    gameWindow.exec();
}

void GameMenu::newGame()
{
    this->sceneId = "1";
    this->startPlay();
}

void GameMenu::showContinueButton()
{
    this->continueButton.show();
}

void GameMenu::setScene(QString sceneId)
{
    this->showContinueButton();
    this->sceneId = sceneId;
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
