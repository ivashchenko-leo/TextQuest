#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent, XmlDom *xmlDoc) :
    QDialog(parent),
    pTimer(new QTimer(this)),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    this->mainLayout = new QVBoxLayout(ui->saContents);
    this->mainLayout->setAlignment(Qt::AlignTop);

    this->xmlDoc = xmlDoc;
    this->cCount = 0;
    this->choiceNotExist = true;
    this->sceneId = "1";
    this->chapter = 0;
    this->tCount = 0;

    this->ui->scrollArea->viewport()->installEventFilter(new MouseFilter(this->ui->scrollArea->viewport(), this));

    if (Settings::instance()->getOption("FullScreen").toBool()) {
        this->showFullScreen();
    } else {
        this->setFixedSize(Settings::Width, Settings::Height);
    }

    if (BASS_Init(-1, 44100, 0, this->winId(), NULL)) {
        BASS_SetVolume(Settings::instance()->getOption(Settings::Volume).toFloat());
    } else {
        qWarning() << "Error! Bass_Init code " << BASS_ErrorGetCode();
    }

    this->ui->scrollArea->setFixedSize(this->size());
    this->ui->saContents->setFixedSize(this->size().width()-10, this->size().height()-10);

    this->createActions();
    connect(this->pTimer, SIGNAL(timeout()), SLOT(showChars()));
}

GameWindow::~GameWindow()
{
    BASS_Free();
    delete ui;
}

void GameWindow::showParagraph(QDomNode paragraph)
{
    this->pText = paragraph.toElement().text();

    QLabel *label = new QLabel();

    label->setWordWrap(true);
    label->setMinimumWidth(this->ui->saContents->size().width()/2);
    label->setMaximumWidth(this->ui->saContents->size().width()-20);
    label->setObjectName("paragraph_" + QString::number(this->tCount));
    this->currentLabel = label;

    this->mainLayout->addWidget(label);

    this->pTimer->start(Settings::instance()->getOption(Settings::TextSpeed).toInt());
}

void GameWindow::showChars()
{
    if (this->cCount < this->pText.size()) {
        this->currentLabel->setText(this->currentLabel->text().append(this->pText.at(this->cCount)));
        this->cCount++;
    } else {
        this->pTimer->stop();
        this->cCount = 0;
    }
}

void GameWindow::showChoices()
{
    QDomNodeList list;

    this->choiceNotExist = false;
    //tCount = -1 becouse inside mousefilter its incrementing, and become 0;
    this->tCount = -1;
    list = this->xmlDoc->getChoiceList(this->scene);

    for (int i = 0; i < list.size(); i++) {
        QLabel *label = new QLabel(list.at(i).toElement().text());

        label->setWordWrap(true);
        label->setMinimumWidth(this->ui->saContents->size().width()/2);
        label->setMaximumWidth(this->ui->saContents->size().width()-20);

        label->installEventFilter(new ChoiceFilter(label, this));
        label->setObjectName(QString::number(i));

        this->mainLayout->addWidget(label);
    }
}

void GameWindow::setScene(QDomNode scene)
{
    this->clrscr();
    this->scene = scene;
}

void GameWindow::clrscr()
{
    QList<QWidget* > list;
    list = this->ui->saContents->findChildren<QWidget* >(QRegExp("^(paragraph_[0-9][0-9]?|[0-9][0-9]?)$"));

    foreach (QWidget *w, list) {
        delete w;
    }
}

void GameWindow::start()
{
    this->scene = this->xmlDoc->getScene(this->sceneId);
    this->chooseAction(this->xmlDoc->getSceneElement(this->scene, this->tCount));
}

void GameWindow::finishParagraph()
{
    for (; this->cCount < this->pText.size(); this->cCount++) {
        this->currentLabel->setText(this->currentLabel->text().append(this->pText.at(this->cCount)));
    }
    this->cCount = 0;
}

void GameWindow::setScene()
{
    this->clrscr();
    this->scene = this->xmlDoc->getScene(this->sceneId);
    if (this->scene.toElement().isNull()) {
        QMessageBox::information(this, tr("Error!"), tr("No such scene with id = %1.").arg(this->sceneId));
        qApp->activeWindow()->close();
    }
}

void GameWindow::chooseAction(QDomNode node)
{
    if (node.toElement().tagName() == GameMenu::PTag) {
        this->showParagraph(node);
    } else {
        if (node.toElement().tagName() == GameMenu::ImageTag) {
            this->showImage(node);
        } else {
            if (node.toElement().tagName() == GameMenu::SoundTag) {
                this->playSound(node);
            } else {
                if (node.toElement().tagName() == GameMenu::ChoiceTag) {
                    this->showChoices();
                } else {
                    this->sendLeftClick();
                    qWarning() << "Unexpected tag! " << node.toElement().tagName();
                }
            }
        }
    }
}

void GameWindow::showImage(QDomNode image)
{
    if (!image.toElement().text().isEmpty()) {
        QImage background(image.toElement().text());
        //background.scaled(this->size())
        if (!background.isNull()) {
            if (background.size().width() > this->size().width()) {
                background = background.scaledToWidth(this->size().width());
            }
            if (background.size().height() > this->size().height()) {
                background = background.scaledToHeight(this->size().height());
            }

            QBrush brush(Qt::TexturePattern);
            brush.setTextureImage(background);

            QPalette palette = this->palette();
            palette.setBrush(QPalette::Background, brush);

            this->setPalette(palette);
        } else {
            qWarning() << QString("No such image %1").arg(image.toElement().text());
        }
    } else {
        qDebug() << "Empty image tag!";
    }
    this->sendLeftClick();
}

void GameWindow::playSound(QDomNode sound)
{
    if (this->stream) {
        if (BASS_ChannelIsActive(this->stream))
            BASS_ChannelStop(this->stream);

        BASS_StreamFree(this->stream);
    }

    bool playback = !sound.toElement().attribute("repeat").isNull();

    if (Settings::instance()->getOption(Settings::Sound).toBool()) {
        this->stream = BASS_StreamCreateFile(FALSE, sound.toElement().text().toUtf8().data(), 0, 0, BASS_UNICODE);
        //this->stream = BASS_StreamCreateFile(FALSE, "Citadel_Underbelly.mp3", 0, 0, BASS_UNICODE);
        qDebug() << sound.toElement().text().toUtf8().data();
        if (this->stream) {
            BASS_ChannelPlay(this->stream, playback);
        } else {
            qWarning() << "Error! Bass_StreamCreateFile code" << BASS_ErrorGetCode();
        }
    }

    this->sendLeftClick();
}

void GameWindow::setChapter()
{
    this->chapter = this->xmlDoc->getChapter(this->sceneId);
}

void GameWindow::sendLeftClick()
{
    QPoint point;
    point.setX(this->size().width()/2);
    point.setY(this->size().height()/2);

    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, point,
                                         Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
    qApp->sendEvent(this->ui->scrollArea->viewport(), event);
}

void GameWindow::setNewFile(QString fileName)
{
    this->xmlDoc->loadXml(fileName);
}

void GameWindow::stuck()
{

}

void GameWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(backAct);
    menu.addAction(skipAct);
    menu.addAction(saveAct);
    menu.addAction(loadAct);
    menu.addAction(color1Act);
    menu.addAction(color2Act);
    menu.addAction(fullScreenAct);
    menu.addAction(menuAct);
    menu.addAction(autoReadAct);
    menu.addAction(changeInterfaceAct);
    menu.exec(event->globalPos());
}

void GameWindow::createActions()
{

    this->backAct = new QAction(tr("&Back"), this);
    //this->backAct->setShortcuts();
    this->backAct->setStatusTip(tr("Return to game"));
    connect(this->backAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->skipAct = new QAction(tr("&Skip"), this);
    //this->skipAct->setShortcuts(QKeySequence::New);
    this->skipAct->setStatusTip(tr("Skip text"));
    connect(this->skipAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->saveAct = new QAction(tr("&Save"), this);
    //this->saveAct->setShortcuts(QKeySequence::New);
    this->saveAct->setStatusTip(tr("Save game"));
    connect(this->saveAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->loadAct = new QAction(tr("&Load"), this);
    //this->loadAct->setShortcuts(QKeySequence::New);
    this->loadAct->setStatusTip(tr("Load game"));
    connect(this->loadAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->color1Act = new QAction(tr("&Color one"), this);
    //this->color1Act->setShortcuts(QKeySequence::New);
    this->color1Act->setStatusTip(tr("Set color one"));
    connect(this->color1Act, SIGNAL(triggered()), this, SLOT(stuck()));

    this->color2Act = new QAction(tr("&Color two"), this);
    //this->color2Act->setShortcuts(QKeySequence::New);
    this->color2Act->setStatusTip(tr("Set color two"));
    connect(this->color2Act, SIGNAL(triggered()), this, SLOT(stuck()));

    this->fullScreenAct = new QAction(tr("&Full screen"), this);
    //this->fullScreenAct->setShortcuts(QKeySequence::New);
    this->fullScreenAct->setStatusTip(tr("Set full screen"));
    connect(this->fullScreenAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->menuAct = new QAction(tr("&Game menu"), this);
    //this->menuAct->setShortcuts(QKeySequence::New);
    this->menuAct->setStatusTip(tr("Return to game menu"));
    connect(this->menuAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->autoReadAct = new QAction(tr("&Auto-read"), this);
    //this->autoReadAct->setShortcuts(QKeySequence::New);
    this->autoReadAct->setStatusTip(tr("Enable auto-read mode"));
    connect(this->autoReadAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->changeInterfaceAct = new QAction(tr("&Change interface"), this);
    //this->changeInterfaceAct->setShortcuts(QKeySequence::New);
    connect(this->changeInterfaceAct, SIGNAL(triggered()), this, SLOT(stuck()));
}











