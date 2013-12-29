#include "mainwindow.h"
#include "ui_mainwindow.h"

SettingsDialog* MainWindow::settings = 0;
HSTREAM MainWindow::stream = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    menu(new GameMenu(this))
{
    ui->setupUi(this);

    MainWindow::settings = new SettingsDialog(this);

    connect(ui->pbOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->pbExit, SIGNAL(clicked()), this, SLOT(exit()));
    connect(ui->pbSettings, SIGNAL(clicked()), this, SLOT(changeSettings()));

    this->ui->pbOpen->installEventFilter(new HoverFilter());
    this->ui->pbExit->installEventFilter(new HoverFilter());
    this->ui->pbSettings->installEventFilter(new HoverFilter());

    this->loadSettings();

    this->setBackgroundImage(QImage(":/backgrounds/book tree.jpg"));
}

void MainWindow::loadSettings()
{
    if (!Settings::instance()->read()) {
        MainWindow::settings->setDefault();
        Settings::instance()->flush();
    } else {
        MainWindow::settings->loadOnUi();
    }
}

void MainWindow::setBackgroundImage(QImage background)
{
    QPalette palette = this->palette();

    background = background.scaled(this->size());

    QBrush brush(Qt::TexturePattern);

    brush.setTextureImage(background);
    palette.setBrush(QPalette::Background, brush);

    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    //QString fileName = "C:/Documents and Settings/Admin/Qt projects/TextQuest/example.xml";
    QString fileName = QFileDialog::getOpenFileName(this,  tr("Open File"), "C:", tr("XML files (*.xml)"));

    if (!fileName.isEmpty()) {
        this->menu->loadXml(fileName);
        this->menu->prepare();
        this->menu->exec();
    }
}

void MainWindow::exit()
{
    QApplication::closeAllWindows();
}

void MainWindow::changeSettings()
{
    MainWindow::settings->loadOnUi();
    MainWindow::settings->exec();
}
