#ifndef SETTINGS_H
#define SETTINGS_H
#define CONFIG_NAME "config.cfg"

#include <QFile>
/*
 * Короче надо дописать сюда пачку свойств, на каждую настройку в форме settingsDialog
 * установить на них геттеры сеттеры, и создать метод типа save() который будет писать все эти свойства в фаил
 * и метод чтения с файла, который бы раскидывал данные по свойствам, это видимо будет конструктор
 **/

class Settings : public QFile
{
    Q_OBJECT

public:
    static Settings* getInstance();

private:
    static Settings* instance;
    explicit Settings(QFile *parent);
    Settings(Settings& root);
    Settings& operator = (Settings&);

signals:
    
public slots:
    
};
#endif // SETTINGS_H
