#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QApplication>
#include "gamemenu.h"
#include "settingsdialog.h"


namespace Ui {
class MainWindow;
}
class SettingsDialog;
class GameMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    static SettingsDialog *settings;
    ~MainWindow();
        
private:
    Ui::MainWindow *ui;

    GameMenu *menu;

private slots:
    void openFile();
    void exit();
    void changeSettings();
};

#endif // MAINWINDOW_H
