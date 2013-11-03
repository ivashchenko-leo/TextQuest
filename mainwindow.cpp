#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbOpen, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(ui->pbExit, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui->pbSettings, SIGNAL(clicked()), this, SLOT(Settings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile()
{
    QString FileName;

    FileName = QFileDialog::getOpenFileName(this,  tr("Open File"), "C:", tr("XML files (*.xml)"));

    if (!FileName.isEmpty())
    {
        //There will be action soon
    }
}

void MainWindow::Exit()
{
    QApplication::closeAllWindows();
}

void MainWindow::Settings()
{

}

