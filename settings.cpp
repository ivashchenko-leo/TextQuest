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

bool Settings::setupAtUi(SettingsDialog* sd)
{
    QObjectList List;

    if (!this->pSettingsMap.isEmpty())
    {


        return true;
    }
    else
    {
        return false;
    }
}

QMap<QString, QVariant>* Settings::getSettings(SettingsDialog* sd)
{
    this->load(this->getWidgets(sd));

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
    this->load(this->getWidgets(sd));
    this->flush();
}

QObjectList Settings::getWidgets(SettingsDialog* sd)
{
    QObjectList List;
    QRegExp re("^(cb|hs)");

    List = sd->children();

    for (int i=0; i < List.size();i++)
    {
        if (re.indexIn(List.at(i)->objectName()) == -1)
        {
            List.removeAt(i);
            i--;
        }
    }

    return List;
}

void Settings::load(QObjectList List)
{
    QStringList reList;
    QRegExp re("^(cb|hs)");

    for (int i=0; i < List.size();i++)
    {
        re.indexIn(List.at(i)->objectName());
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
