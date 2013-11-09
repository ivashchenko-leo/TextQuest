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
    void save(SettingsDialog* sd);
    QMap<QString, QVariant>* getSettings(SettingsDialog* sd);
    bool setupAtUi(SettingsDialog* sd);

private:
    QFile* file;
    SettingsDialog* pSd;
    QMap<QString, QVariant> pSettingsMap;
    QObjectList getWidgets(SettingsDialog* sd);
    void flush();
    void load(QObjectList List);

    static Settings* instance;
    explicit Settings();
    Settings(Settings& root);
    Settings& operator = (Settings&);


};
#endif // SETTINGS_H
