#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>
#include <QRegExp>
#include "settings.h"
#include <QMouseEvent>
#include <QMessageBox>
//#include <QPoint>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;

protected:
    //virtual void mousePressEvent(QMouseEvent* mouse);

private slots:
    void changeColor();
    void acceptSettings();
    void rejectSettings();
    void changeFont();
};

#endif // SETTINGSDIALOG_H
