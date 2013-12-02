#include "settings.h"
Settings* Settings::self = 0;
const QString Settings::FileName("config.cfg");
const QString Settings::TextSpeed("TextSpeed");
const QString Settings::Volume("Volume");
const QString Settings::AutoRead("AutoRead");
const QString Settings::FullScreen("FullScreen");
const QString Settings::SkipAfterChoice("SkipAfterChoice");
const QString Settings::SkipUnreadText("SkipUnreadText");
const QString Settings::Sound("Sound");
const QString Settings::Interface("Interface");
const int Settings::Width = 1024;
const int Settings::Height = 768;
const int Settings::ColorCount = 2;

Settings::Settings() :
    QObject(),
    file(new QFile(Settings::FileName))
{
}

Settings* Settings::instance()
{
    if(!Settings::self) {
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
    if (this->colors.count() == Settings::ColorCount) {
        this->colors.replace(number, color);
    } else {
        this->colors.append(color);
    }
}

void Settings::setOption(QFont font)
{
    this->font = font;
}

bool Settings::read()
{
    this->file->open(QIODevice::ReadOnly);
    QDataStream stream(this->file);

    stream.setVersion(QDataStream::Qt_4_8);
    stream >> this->settings >> this->colors >> this->font;

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

    if(stream.status() != QDataStream::Ok) {
        QMessageBox::critical(0,
                              tr("Error!"),
                              tr("Can't write into the file ") + Settings::FileName);
    } else {
        this->file->flush();
    }

    this->file->close();
}

