#ifndef SETTINGS_H
#define SETTINGS_H

#define CONFIG_NAME "config.cfg"
#define TRUE_STRING "true"
#define FALSE_STRING "false"

#include <QFile>
#include <QMap>
/*
 * Короче надо дописать сюда пачку свойств, на каждую настройку в форме settingsDialog
 * установить на них геттеры сеттеры, и создать метод типа save() который будет писать все эти свойства в фаил
 * и метод чтения с файла, который бы раскидывал данные по свойствам
 **/

class Settings : public QFile
{
    Q_OBJECT

public:
    static Settings* getInstance();
    void Settings::readSettings();
    void Settings::save();

private:
    QMap<QString, QString> pSettingsMap;

    static Settings* instance;
    explicit Settings(QFile *parent);
    Settings(Settings& root);
    Settings& operator = (Settings&);

signals:
    
public slots:
    void setUnreadText(bool status);
    void setAutoRead(bool status);
    void setAfterChoice(bool status);
    void setFullScreen(bool status);
    void setSound(bool status);
};
#endif // SETTINGS_H
