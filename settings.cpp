#include "settings.h"
Settings* Settings::instance = 0;

Settings::Settings(QFile* parent) :
    QFile(parent)
{

}

Settings* Settings::getInstance()
{
    QFile file(CONFIG_NAME);

    if(!instance)
    {
        if (!file.exists())
        {
            file.open(QIODevice::ReadWrite);
        }

        instance = new Settings(&file);
    }

    return instance;
}

void Settings::readSettings()
{

}

void Settings::save()
{

}

void Settings::setUnreadText(bool status)
{
    this->pSettingsMap["UnreadText"] = status ? TRUE_STRING : FALSE_STRING;
}

void Settings::setAutoRead(bool status)
{
    this->pSettingsMap["AutoRead"] = status ? TRUE_STRING : FALSE_STRING;
}

void Settings::setAfterChoice(bool status)
{
    this->pSettingsMap["AfterChoice"] = status ? TRUE_STRING : FALSE_STRING;
}

void Settings::setFullScreen(bool status)
{
    this->pSettingsMap["FullScreen"] = status ? TRUE_STRING : FALSE_STRING;
}

void Settings::setSound(bool status)
{
    this->pSettingsMap["Sound"] = status ? TRUE_STRING : FALSE_STRING;
}
