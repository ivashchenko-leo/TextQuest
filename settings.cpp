#include "settings.h"
Settings* Settings::self = 0;
const QString Settings::fileName = "config.cfg";


Settings::Settings() :
    QObject(),
    file(new QFile(Settings::fileName))
{
}

Settings* Settings::instance()
{
    if(!Settings::self)
    {
        Settings::self = new Settings();
    }

    return Settings::self;
}

QColor Settings::getColor(int number)
{
    return this->colors.at(number);
}

QVariant Settings::getOption(QString option)
{
    return this->settings.value(option);
}

QFont Settings::getFont()
{
    return this->font;
}

void Settings::setOption(QString key, QVariant value)
{
    this->settings.insert(key, value);
}

void Settings::setOption(int number, QColor color)
{
    if (this->colors.at(number).isValid()) {
        this->colors.replace(number, color);
    } else {
        this->colors.insert(number, color);
    }
//    qDebug() << this->colors.at(number) << number;
}

void Settings::setOption(QFont font)
{
    this->font = font;
}
//void Settings::setupAtUi(SettingsDialog* sd)
//{
//    if (this->pSettingsMap.isEmpty())
//    {
//        this->setSettings(this->FromUi, sd);
//        this->flush();
//    }
//    else
//    {
//        this->setSettings(this->OnUi, sd);
//    }
//}

//void Settings::setTextColor(QColor color)
//{
//    this->color = color;
//}

//QColor Settings::getTextColor()
//{
//    if (!this->color.isValid())
//    {
//        this->color.setRgb(0,0,0);
//    }

//    return this->color;
//}

//void Settings::setFont(QFont font)
//{
//    this->font = font;
//}

//QFont Settings::getFont()
//{
//    if (this->font.family().isEmpty())
//    {
//        this->font.fromString(QString("Arial,14,-1,5,75,0,0,0,0,0"));
//    }

//    return this->font;
//}

//QMap<QString, QVariant>* Settings::getSettings()
//{
//    return &this->pSettingsMap;
//}

bool Settings::read()
{
    this->file->open(QIODevice::ReadOnly);

    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream >> this->settings >> this->colors >> this->font;

//    foreach (QString key, this->pSettingsMap.keys())
//    {
//        qDebug() << this->pSettingsMap.value(key);
//    }
    this->file->close();

    if (stream.status() != QDataStream::Ok) {
        return false;
    }
    return true;
}

void Settings::flush()
{
    this->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream << this->settings << this->colors << this->font;

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

//void Settings::setSettings(int mode, SettingsDialog* sd)
//{
//    QObjectList List;
//    QRegExp re("^(cb|hs)");
//    QStringList reList;

//    List = sd->children();

//    for (int i=0; i < List.size();i++)
//    {
//        if (re.indexIn(List.at(i)->objectName()) == -1)
//        {
//            List.removeAt(i);
//            i--;
//        }
//        else
//        {
//            re.indexIn(List.at(i)->objectName());
//            reList = re.capturedTexts();

//            if (reList.at(1) == QString("cb"))
//            {
//                if (mode == this->OnUi)
//                {
//                    ((QCheckBox* )List.at(i))->setChecked(this->pSettingsMap[List.at(i)->objectName()].toBool());
//                    //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toBool();
//                }
//                else
//                {
//                    this->pSettingsMap.insert(List.at(i)->objectName(), ((QCheckBox* )List.at(i))->isChecked());
//                    //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toBool();
//                }
//            }
//            else
//            {
//                if (reList.at(1) == QString("hs"))
//                {
//                    if (mode == this->OnUi)
//                    {
//                        ((QSlider* )List.at(i))->setValue(this->pSettingsMap[List.at(i)->objectName()].toInt());
//                        //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toInt();
//                    }
//                    else
//                    {
//                        this->pSettingsMap.insert(List.at(i)->objectName(), ((QSlider* )List.at(i))->value());
//                        //qDebug() << List.at(i)->objectName() << this->pSettingsMap[List.at(i)->objectName()].toInt();
//                    }
//                }
//            }
//        }
//    }
//}
