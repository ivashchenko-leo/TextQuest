#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent, XmlDom *xmlDoc) :
    QDialog(parent),
    ui(new Ui::GameWindow),
    pTimer(new QTimer(this))
{
    ui->setupUi(this);
    this->xmlDoc = xmlDoc;
    this->cCount = 0;
    this->choiceNotExist = true;
    this->sCount = 0;
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
    this->choiceNotExist = false;
    list = this->xmlDoc->getChoiceList(this->scene);
    for (int i = 0; i < list.size(); i++) {
        QPushButton *button = new QPushButton(list.at(i).toElement().text(), this);
        button->show();
    }
}

void GameWindow::setScene(QDomNode scene)
{
    this->scene = scene;
}

void GameWindow::start()
{
    this->scene = this->xmlDoc->getScene(this->xmlDoc->getChapter(this->chapter), this->sCount);
    this->chooseAction(this->xmlDoc->getSceneElement(this->scene, this->tCount));
}
/*
void GameWindow::mousePressEvent(QMouseEvent *mouse)
{
    qDebug() << "mouse pressed";
    if (mouse->button() & Qt::LeftButton) {
        if (this->pTimer->isActive()) {
            this->pTimer->stop();
            this->finishParagraph();
        } else {
            this->tCount++;
            this->showParagraph(this->tCount);
        }
    }
}
*/
void GameWindow::finishParagraph()
{
    for (; this->cCount < this->pText.size(); this->cCount++) {
        this->ui->textBrowser->insertPlainText(this->pText.at(this->cCount));
    }
    this->cCount = 0;
}

void GameWindow::setScene()
{
    this->scene = this->xmlDoc->getScene(this->xmlDoc->getChapter(this->chapter),this->sCount);
}

void GameWindow::chooseAction(QDomNode node)
{
    qDebug () << node.toElement().tagName();
    if (node.toElement().tagName() == GameMenu::PTag) {
        this->showParagraph(node);
    } else {
        if (node.toElement().tagName() == GameMenu::ImageTag) {
            qDebug() << "Image tag!";
        } else {
            if (node.toElement().tagName() == GameMenu::SoundTag) {
                qDebug() << "Sound tag!";
            } else {
                if (node.toElement().tagName() == GameMenu::ChoiceTag) {
                    this->showChoices();
                } else {
                    qDebug() << "Unexpected tag!";
                }
            }
        }
    }
}







