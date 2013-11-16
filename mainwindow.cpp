#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pSettingsDialog(new SettingsDialog(this)),
  pGameMenu(new GameMenu(this))
{
    ui->setupUi(this);
    connect(ui->pbOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->pbExit, SIGNAL(clicked()), this, SLOT(exit()));
    connect(ui->pbSettings, SIGNAL(clicked()), this, SLOT(changeSettings()));

    if (!Settings::instance()->read()) {
        this->pSettingsDialog->setDefault();
        Settings::instance()->flush();
    } else {
        this->pSettingsDialog->loadOnUi();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,  tr("Open File"), "C:", tr("XML files (*.xml)"));

    if (!fileName.isEmpty()) {
        this->pGameMenu->loadXml(fileName);
        this->pGameMenu->exec();
    }
}

void MainWindow::exit()
{
    QApplication::closeAllWindows();
}

void MainWindow::changeSettings()
{
    this->pSettingsDialog->exec();
}

