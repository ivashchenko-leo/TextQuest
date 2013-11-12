#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>
#include "settings.h"
#include <QMessageBox>

namespace Ui {
class SettingsDialog;
}
class Settings;

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void setDefault();
    void loadOnUi();

private:
    Ui::SettingsDialog *ui;
    Settings *settings;
    void loadFromUi();

protected:
    //virtual void mousePressEvent(QMouseEvent* mouse);

private slots:
    void changeColorOne();
    void changeColorTwo();
    void acceptSettings();
    void changeFont();
};

#endif // SETTINGSDIALOG_H
