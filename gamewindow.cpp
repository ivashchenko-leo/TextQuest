#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent, XmlDom *xmlDoc) :
    QDialog(parent),
    pTimer(new QTimer(this)),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->xmlDoc = xmlDoc;
    this->cCount = 0;
    this->choiceNotExist = true;
    this->sceneId = "1";
    this->chapter = 0;
    this->tCount = 0;
    this->ui->textBrowser->viewport()->installEventFilter(new MouseFilter(this->ui->textBrowser, this));
    connect(this->pTimer, SIGNAL(timeout()), SLOT(showChars()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showParagraph(QDomNode paragraph)
{
    this->pText = paragraph.toElement().text() + "\n";
    this->pTimer->start(Settings::instance()->getOption(Settings::TextSpeed).toInt());
}

void GameWindow::showChars()
{
    if (this->cCount < this->pText.size()) {
        this->ui->textBrowser->moveCursor(QTextCursor::End);
        this->ui->textBrowser->insertPlainText(this->pText.at(this->cCount));
        this->cCount++;
    } else {
        this->pTimer->stop();
        this->cCount = 0;
    }
}

void GameWindow::showChoices()
{
    QDomNodeList list;
    int height = 0;
    this->ui->textBrowser->insertPlainText("\n");
    this->choiceNotExist = false;
    //tCount = -1 becouse inside mousefilter its incrementing, and become 0;
    this->tCount = -1;
    list = this->xmlDoc->getChoiceList(this->scene);

    for (int i = 0; i < list.size(); i++) {
        QLabel *button = new QLabel(list.at(i).toElement().text(), this);
        button->setWordWrap(true);
        button->move(5, this->ui->textBrowser->cursorRect().y() + i * height);
        button->setMinimumWidth(this->size().width());
        height = button->size().height();

        button->installEventFilter(new ChoiceFilter(button, this));
        button->setObjectName(QString::number(i));
        button->show();
    }
}

void GameWindow::setScene(QDomNode scene)
{
    this->ui->textBrowser->clear();
    this->scene = scene;
}

void GameWindow::start()
{
    this->scene = this->xmlDoc->getScene(this->sceneId);
    this->chooseAction(this->xmlDoc->getSceneElement(this->scene, this->tCount));
}

void GameWindow::finishParagraph()
{
    for (; this->cCount < this->pText.size(); this->cCount++) {
        this->ui->textBrowser->insertPlainText(this->pText.at(this->cCount));
    }
    this->cCount = 0;
}

void GameWindow::setScene()
{
    this->ui->textBrowser->clear();
    this->scene = this->xmlDoc->getScene(this->sceneId);
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
                    qDebug() << "Unexpected tag! " << node.toElement().tagName();
                }
            }
        }
    }
}

void GameWindow::showImage(QDomNode image)
{
    this->sendLeftClick();
}

void GameWindow::playSound(QDomNode sound)
{
    this->sendLeftClick();
}

void GameWindow::setChapter()
{
    this->chapter = this->xmlDoc->getChapter(this->sceneId);
}

void GameWindow::sendLeftClick()
{
    QPoint point;
    point.setX(this->ui->textBrowser->size().width()/2);
    point.setY(this->ui->textBrowser->size().height()/2);

    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, point,
                                         Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
    qApp->sendEvent(this->ui->textBrowser->viewport(), event);
}

void GameWindow::setNewFile(QString fileName)
{
    this->xmlDoc->loadXml(fileName);
}

void GameWindow::deleteChoices()
{
    QRegExp regex("^[0-9]{1,2}$");
    QList<QWidget *> list = this->findChildren<QWidget *>(regex);
    foreach (QWidget * widget, list) {
        delete widget;
    }
    this->sendLeftClick();
}

