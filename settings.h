#ifndef SETTINGS_H
#define SETTINGS_H

#define TRUE_STRING "true"
#define FALSE_STRING "false"

#include <QFile>
#include <QMap>
#include "settingsdialog.h"
#include <QtGui>

class SettingsDialog;

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings* getInstance();
    void read();
    QMap<QString, QVariant>* getSettings();
    void setupAtUi(SettingsDialog* sd);
    void setTextColor(QColor color);
    void setFont(QFont font);
    QFont getFont();
    QColor getTextColor();
    void setSettings(int mode, SettingsDialog* sd);
    void flush();
    enum mode {OnUi, FromUi};

private:
    QFile* file;
    QMap<QString, QVariant> pSettingsMap;
    QColor color;
    QFont font;

    static Settings* instance;
    explicit Settings();
    Settings(Settings& root);
    Settings& operator = (Settings&);


};
#endif // SETTINGS_H
