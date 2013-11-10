#include "settings.h"
Settings* Settings::instance = 0;

Settings::Settings() :
    QObject(),
    file(new QFile(QString("config.cfg")))
{
}

Settings* Settings::getInstance()
{
    if(!instance)
    {
        instance = new Settings();
    }

    return instance;
}

void Settings::setupAtUi(SettingsDialog* sd)
{
    if (this->pSettingsMap.isEmpty())
    {
        this->setSettings(this->FromUi, sd);
        this->flush();
    }
    else
    {
        this->setSettings(this->OnUi, sd);
    }
}

void Settings::setTextColor(QColor color)
{
    this->color = color;
}

QColor Settings::getTextColor()
{
    if (!this->color.isValid())
    {
        this->color.setRgb(0,0,0);
    }

    return this->color;
}

void Settings::setFont(QFont font)
{
    this->font = font;
}

QFont Settings::getFont()
{
    if (this->font.family().isEmpty())
    {
        this->font.fromString(QString("Arial,6,-1,5,75,0,0,0,0,0"));
    }

    return this->font;
}

QMap<QString, QVariant>* Settings::getSettings()
{
    return &this->pSettingsMap;
}

void Settings::read()
{
    this->file->open(QIODevice::ReadOnly);

    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream >> this->pSettingsMap >> this->color >> this->font;

//    foreach (QString key, this->pSettingsMap.keys())
//    {
//        qDebug() << this->pSettingsMap.value(key);
//    }

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Error at reading file";
    }

    this->file->close();
}

void Settings::flush()
{
    this->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream << this->pSettingsMap << this->getTextColor() << this->getFont();

//    foreach (QString key, this->pSettingsMap.keys())
//    {
//        qDebug() << this->pSettingsMap.value(key);
//    }

    if(stream.status() != QDataStream::Ok)
    {
        qDebug() << "Error at writing file";
    }

    this->file->flush();
    this->file->close();
}

void Settings::setSettings(int mode, SettingsDialog* sd)
{
    QObjectList List;
    QRegExp re("^(cb|hs)");
    QStringList reList;

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
            re.indexIn(List.at(i)->objectName());
            reList = re.capturedTexts();

            if (reList.at(1) == QString("cb"))
            {
                if (mode == this->OnUi)
                {
                    ((QCheckBox* )List.at(i))->setChecked(this->pSettingsMap[List.at(i)->objectName()].toBool());
                    //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toBool();
                }
                else
                {
                    this->pSettingsMap.insert(List.at(i)->objectName(), ((QCheckBox* )List.at(i))->isChecked());
                    //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toBool();
                }
            }
            else
            {
                if (reList.at(1) == QString("hs"))
                {
                    if (mode == this->OnUi)
                    {
                        ((QSlider* )List.at(i))->setValue(this->pSettingsMap[List.at(i)->objectName()].toInt());
                        //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toInt();
                    }
                    else
                    {
                        this->pSettingsMap.insert(List.at(i)->objectName(), ((QSlider* )List.at(i))->value());
                        //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toInt();
                    }
                }
            }
        }
    }
}
