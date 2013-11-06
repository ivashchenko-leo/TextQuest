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
        if (file.exists())
        {
            file.open(QIODevice::ReadWrite);
        }

        instance = new Settings(&file);
    }

    return instance;
}


