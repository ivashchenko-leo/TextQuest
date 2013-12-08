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
    this->textColor = Settings::instance()->getColor(0);

    this->ui->scrollArea->viewport()->installEventFilter(new MouseFilter(this->ui->scrollArea->viewport(), this));

    this->setResolution(Settings::instance()->getOption(Settings::FullScreen).toBool());

    this->createActions();
    connect(this->pTimer, SIGNAL(timeout()), SLOT(showChars()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setResolution(bool fullScreen)
{
    if (fullScreen) {
        this->showFullScreen();
    } else {
        this->showNormal();
        this->setFixedSize(Settings::Width, Settings::Height);
    }

    this->ui->scrollArea->setFixedSize(this->size());
    this->ui->saContents->setFixedSize(this->size().width()-10, this->size().height()-10);

    QList<QWidget *> list = this->ui->saContents->findChildren<QWidget* >(QRegExp("^(paragraph_[0-9][0-9]?|[0-9][0-9]?)$"));

    if (!list.isEmpty()) {
        foreach (QWidget *w, list) {
            w->setFixedWidth(this->ui->saContents->size().width()-20);
            w->setFixedHeight(w->heightForWidth(this->ui->saContents->size().width()-20));
        }
    }
}

void GameWindow::showParagraph(QDomNode paragraph)
{
    this->pText = paragraph.toElement().text();

    QLabel *label = new QLabel();
    QPalette palette;

    palette.setColor(label->foregroundRole(), this->textColor);

    label->setWordWrap(true);
    label->setPalette(palette);
    label->setFont(Settings::instance()->getFont());
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
    QPalette palette;

    this->choiceNotExist = false;
    //tCount = -1 becouse inside mousefilter its incrementing, and become 0;
    this->tCount = -1;
    list = this->xmlDoc->getChoiceList(this->scene);

    for (int i = 0; i < list.size(); i++) {
        QLabel *label = new QLabel(list.at(i).toElement().text());

        palette.setColor(label->foregroundRole(), this->textColor);
        label->setWordWrap(true);
        label->setPalette(palette);
        label->setFont(Settings::instance()->getFont());
        label->setMinimumWidth(this->ui->saContents->size().width()/2);
        label->setMaximumWidth(this->ui->saContents->size().width()-20);

        label->installEventFilter(new ChoiceFilter(label, this));
        label->setObjectName(QString::number(i));

        this->mainLayout->addWidget(label);
    }
}

void GameWindow::showImage(QDomNode image)
{
    if (!image.toElement().text().isEmpty()) {
        QImage background(image.toElement().text());

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
    if (MainWindow::stream != 0) {
        if (BASS_ChannelIsActive(MainWindow::stream))
            BASS_ChannelStop(MainWindow::stream);

        BASS_StreamFree(MainWindow::stream);
    }

    bool restart = !sound.toElement().attribute("repeat").isNull();
    //QString name = QFileDialog::getOpenFileName(this,  tr("Open File"), "C:", tr(""));
    char *fileName = sound.toElement().text().toUtf8().data();
    //char *fileName = name.toUtf8().data();

    if (Settings::instance()->getOption(Settings::Sound).toBool()) {
        if (!sound.toElement().text().isEmpty()) {
            MainWindow::stream = BASS_StreamCreateFile(FALSE, fileName, 0, 0, BASS_UNICODE);
            //this->stream = BASS_StreamCreateFile(FALSE, "Citadel_Underbelly.mp3", 0, 0, BASS_UNICODE);
            if (MainWindow::stream != 0) {
                BASS_SetVolume(Settings::instance()->getOption(Settings::Volume).toFloat()/100.0);
                BASS_ChannelPlay(MainWindow::stream, restart);
            } else {
                qWarning() << "Error! Bass_StreamCreateFile code" << BASS_ErrorGetCode();
            }
        }
    }

    this->sendLeftClick();
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

    if (!list.isEmpty()) {
        foreach (QWidget *w, list) {
            delete w;
        }
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
    menu.addSeparator();
    menu.addAction(skipAct);
    menu.addAction(autoReadAct);
    menu.addAction(changeInterfaceAct);
    menu.addSeparator();
    menu.addAction(saveAct);
    menu.addAction(loadAct);
    menu.addSeparator();
    menu.addAction(toggleColorAct);
    menu.addAction(fullScreenAct);
    menu.addAction(menuAct);

    menu.exec(event->globalPos());
}

void GameWindow::skipText()
{

}

void GameWindow::toggleFullScreen()
{
    bool fullScreen = !Settings::instance()->getOption(Settings::FullScreen).toBool();
    Settings::instance()->setOption(Settings::FullScreen, QVariant(fullScreen));

    this->setResolution(fullScreen);
}

void GameWindow::toggleColor()
{
    static int colorNumber = 0;
    QPalette palette;

    colorNumber == 1 ? colorNumber = 0 : colorNumber = 1;
    this->textColor = Settings::instance()->getColor(colorNumber);

    QList<QLabel *> list = this->ui->saContents->findChildren<QLabel *>(QRegExp("^(paragraph_[0-9][0-9]?|[0-9][0-9]?)$"));

    if (!list.isEmpty()) {
        foreach (QLabel *label, list) {
            palette.setColor(label->foregroundRole(), this->textColor);
            label->setPalette(palette);
        }
    }
}

void GameWindow::createActions()
{
    this->backAct = new QAction(tr("&Back"), this);
    this->backAct->setStatusTip(tr("Return to game"));
    connect(this->backAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->skipAct = new QAction(tr("&Skip"), this);
    this->skipAct->setShortcut(Qt::SHIFT + Qt::Key_S);
    this->skipAct->setStatusTip(tr("Skip text"));
    connect(this->skipAct, SIGNAL(triggered()), this, SLOT(skipText()));

    this->saveAct = new QAction(tr("&Save"), this);
    this->saveAct->setShortcut(Qt::Key_F5);
    this->saveAct->setStatusTip(tr("Save game"));
    connect(this->saveAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->loadAct = new QAction(tr("&Load"), this);
    this->loadAct->setShortcut(Qt::Key_F6);
    this->loadAct->setStatusTip(tr("Load game"));
    connect(this->loadAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->toggleColorAct = new QAction(tr("&Toggle color"), this);
    this->toggleColorAct->setShortcut(Qt::MiddleButton);
    this->toggleColorAct->setStatusTip(tr("Set color one/two"));
    connect(this->toggleColorAct, SIGNAL(triggered()), this, SLOT(toggleColor()));

    this->fullScreenAct = new QAction(tr("&Full screen"), this);
    this->fullScreenAct->setShortcut(Qt::ALT + Qt::Key_Enter);
    this->fullScreenAct->setStatusTip(tr("Set full screen"));
    connect(this->fullScreenAct, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));

    this->menuAct = new QAction(tr("&Game menu"), this);
    this->menuAct->setShortcut(Qt::Key_Escape);
    this->menuAct->setStatusTip(tr("Return to game menu"));
    connect(this->menuAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->autoReadAct = new QAction(tr("&Auto-read"), this);
    this->autoReadAct->setShortcut(Qt::SHIFT + Qt::Key_A);
    this->autoReadAct->setStatusTip(tr("Enable auto-read mode"));
    connect(this->autoReadAct, SIGNAL(triggered()), this, SLOT(stuck()));

    this->changeInterfaceAct = new QAction(tr("&Change interface"), this);
    this->changeInterfaceAct->setShortcut(Qt::SHIFT + Qt::Key_D);
    connect(this->changeInterfaceAct, SIGNAL(triggered()), this, SLOT(stuck()));
}











