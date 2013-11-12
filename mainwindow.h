#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include "gamemenu.h"
#include "settingsdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
        
private:
    Ui::MainWindow *ui;
    SettingsDialog* pSettingsDialog;
    GameMenu* pGameMenu;

private slots:
    void openFile();
    void exit();
    void changeSettings();
};

#endif // MAINWINDOW_H
