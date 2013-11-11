#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFile>
#include <QMap>
#include "settingsdialog.h"
#include <QtGui>

class SettingsDialog;

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings *instance();
    bool read();
//    QMap<QString, QVariant>* getSettings();
//    void setupAtUi(SettingsDialog* sd);
//    void setTextColor(QColor color);
//    void setFont(QFont font);
//    QFont getFont();
//    QColor getTextColor();
//    void setSettings(int mode, SettingsDialog* sd);
    void flush();
//    enum mode {OnUi, FromUi};
    QColor getColor(int number);
    QVariant getOption(QString option);
    QFont getFont();
    void setOption(QString key, QVariant value);
    void setOption(int number, QColor color);
    void setOption(QFont font);
    const static QString fileName;

private:
    QFile *file;
    QMap<QString, QVariant> settings;
    QVector<QColor> colors;
    QFont font;

    static Settings *self;
    explicit Settings();
    Settings(Settings& root);
    Settings& operator = (Settings&);


};
#endif // SETTINGS_H
