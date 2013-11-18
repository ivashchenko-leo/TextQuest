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
    this->sCount = 0;
    this->chapter = 0;
    this->pCount = 0;
    this->scene = this->xmlDoc->getScene(this->xmlDoc->getChapter(this->chapter), this->sCount);
    this->showParagraph(this->xmlDoc->getP(this->scene, this->pCount));
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
            this->pCount++;
            this->showParagraph(this->pCount);
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









