#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>

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

private slots:
    void changeColor();
    void acceptSettings();
    void changeFont();
};

#endif // SETTINGSDIALOG_H
