#include "settings.h"
Settings* Settings::instance = 0;

Settings::Settings() :
    QObject(),
    file(new QFile(QString("config.bin")))
{
    this->file->open(QIODevice::ReadWrite);
}

Settings* Settings::getInstance()
{
    if(!instance)
    {
        instance = new Settings();
    }

    return instance;
}

QMap<QString, QVariant>* Settings::getSettings(SettingsDialog* sd)
{
    this->load(sd);

    return &this->pSettingsMap;
}

void Settings::read()
{
    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream >> this->pSettingsMap;
}

void Settings::flush()
{
    QDataStream stream(this->file);

    if (this->pSettingsMap.isEmpty())
    {
        this->read();
    }

    stream.setVersion(QDataStream::Qt_4_8);
    stream << this->pSettingsMap;
}

void Settings::save(SettingsDialog* sd)
{
    this->load(sd);
    this->flush();
}

void Settings::load(SettingsDialog* sd)
{
    QStringList reList;
    QRegExp re("^(cb|hs)");
    QObjectList List;

    List = sd->children();

    for (int i=0; i < List.size();i++)
    {
        if (re.indexIn(List.at(i)->objectName()) == -1)
        {
            List.removeAt(i);
            i--;
        }
        else
        {
            reList = re.capturedTexts();

            if (reList.at(1) == QString("cb"))
            {
                this->pSettingsMap.insert(List.at(i)->objectName(), ((QCheckBox* )List.at(i))->isChecked());
            }
            else
            {
                if (reList.at(1) == QString("hs"))
                {
                    this->pSettingsMap.insert(List.at(i)->objectName(), ((QSlider* )List.at(i))->value());
                }
            }
        }
    }
}
