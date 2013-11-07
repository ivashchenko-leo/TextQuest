#ifndef SETTINGS_H
#define SETTINGS_H

#define CONFIG_NAME "config.cfg"
#define TRUE_STRING "true"
#define FALSE_STRING "false"

#include <QFile>
#include <QMap>
/*
 * Не нравится мне этот класс, надо как то избавиться от такого количества слотов (по 1 на каждую кнопку),
 * заменить чем то одним евент, не евент, отловить просто клик на кнопку, любую, потом получить обьект кнопки,
 * передать его в этот класс в один и тот же метод или слот, и все, победа, таким образом при добавлении
 * новых кнопок в этом классе ничего менять не придется, или придется, но не так много.
 **/

class Settings : public QFile
{
    Q_OBJECT

public:
    static Settings* getInstance();
    void readSettings();
    void save();

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
