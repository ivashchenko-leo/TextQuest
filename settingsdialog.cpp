#include "settingsdialog.h"
#include "ui_settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings(Settings::instance())
{
    ui->setupUi(this);

    connect(ui->pbOk, SIGNAL(clicked()), SLOT(acceptSettings()));
    connect(ui->tbColor1, SIGNAL(clicked()), SLOT(changeColorOne()));
    connect(ui->tbColor2, SIGNAL(clicked()), SLOT(changeColorTwo()));
    connect(ui->tbFont, SIGNAL(clicked()), SLOT(changeFont()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setDefault()
{
    this->loadFromUi();
    this->settings->setOption(0, QColor(0, 0, 0));
    this->settings->setOption(1, QColor(255, 255, 255));
    this->settings->setOption(QFont("Arial"));
}

void SettingsDialog::loadOnUi()
{
    ui->cbAutoRead->setChecked(this->settings->getOption(Settings::AutoRead).toBool());
    ui->cbFullScreen->setChecked(this->settings->getOption(Settings::FullScreen).toBool());
    ui->cbSkipAfterChoice->setChecked(this->settings->getOption(Settings::SkipAfterChoice).toBool());
    ui->cbSkipUnreadText->setChecked(this->settings->getOption(Settings::SkipUnreadText).toBool());
    ui->cbSound->setChecked(this->settings->getOption(Settings::Sound).toBool());
    ui->hsSpeed->setValue(this->settings->getOption(Settings::TextSpeed).toInt());
    ui->hsVolume->setValue(this->settings->getOption(Settings::Volume).toInt());
}

void SettingsDialog::loadFromUi()
{
    this->settings->setOption(Settings::TextSpeed, QVariant(ui->hsSpeed->value()));
    this->settings->setOption(Settings::Volume, QVariant(ui->hsVolume->value()));
    this->settings->setOption(Settings::AutoRead, QVariant(ui->cbAutoRead->isChecked()));
    this->settings->setOption(Settings::FullScreen, QVariant(ui->cbFullScreen->isChecked()));
    this->settings->setOption(Settings::SkipAfterChoice, QVariant(ui->cbSkipAfterChoice->isChecked()));
    this->settings->setOption(Settings::SkipUnreadText, QVariant(ui->cbSkipUnreadText->isChecked()));
    this->settings->setOption(Settings::Sound, QVariant(ui->cbSound->isChecked()));
}

void SettingsDialog::changeColorOne()
{
    QColor Color = QColorDialog::getColor(this->settings->getColor(0), this);
    if (Color.isValid()) {
        this->settings->setOption(0, Color);
        this->settings->flush();
    }
}

void SettingsDialog::changeColorTwo()
{
    QColor Color = QColorDialog::getColor(this->settings->getColor(1), this);
    if (Color.isValid()) {
        this->settings->setOption(1, Color);
        this->settings->flush();
    }
}

void SettingsDialog::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this->settings->getFont(), this);

    if (ok) {
        this->settings->setOption(font);
        this->settings->flush();
    }
}

void SettingsDialog::acceptSettings()
{
    this->loadFromUi();
    this->settings->flush();
    this->accept();
}










