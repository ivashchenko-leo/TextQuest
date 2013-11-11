#include "settingsdialog.h"
#include "ui_settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings(Settings::instance())
{
    ui->setupUi(this);

    connect(ui->pbOk, SIGNAL(clicked()), this, SLOT(acceptSettings()));
    connect(ui->tbColor1, SIGNAL(clicked()), this, SLOT(changeColorOne()));
    connect(ui->tbColor2, SIGNAL(clicked()), this, SLOT(changeColorTwo()));
    connect(ui->tbFont, SIGNAL(clicked()), this, SLOT(changeFont()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setDefault()
{
    this->settings->setOption(QString("TextSpeed"), QVariant(ui->hsSpeed->value()));
    this->settings->setOption(QString("Brightness"), QVariant(ui->hsBrightness->value()));
    this->settings->setOption(QString("Transparency"), QVariant(ui->hsTransparency->value()));
    this->settings->setOption(QString("Volume"), QVariant(ui->hsVolume->value()));
    this->settings->setOption(QString("AutoRead"), QVariant(ui->cbAutoRead->isChecked()));
    this->settings->setOption(QString("FullScreen"), QVariant(ui->cbFullScreen->isChecked()));
    this->settings->setOption(QString("SkipAfterChoice"), QVariant(ui->cbSkipAfterChoice->isChecked()));
    this->settings->setOption(QString("SkipUnreadText"), QVariant(ui->cbSkipUnreadText->isChecked()));
    this->settings->setOption(QString("Sound"), QVariant(ui->cbSound->isChecked()));
    this->settings->setOption(1, QColor(0, 0, 0));
    this->settings->setOption(2, QColor(255, 255, 255));
    this->settings->setOption(QFont("Arial"));
}

void SettingsDialog::changeColorOne()
{
    QColor Color = QColorDialog::getColor(this->settings->getColor(1), this);
    if (Color.isValid()) {
        this->settings->setOption(1, Color);
        this->settings->flush();
    }
}

void SettingsDialog::changeColorTwo()
{
    QColor Color = QColorDialog::getColor(this->settings->getColor(2), this);
    if (Color.isValid()) {
        this->settings->setOption(2, Color);
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
    this->settings->flush();
    this->accept();
}

/*virtual*/
/*void SettingsDialog::mousePressEvent(QMouseEvent* mouse)
{
    QPoint coord;
    QWidget* widget;

    coord = mouse->pos();
    widget = qApp->widgetAt(this->mapToGlobal(coord));
    QMessageBox::information(this, "Title", widget->objectName());
    //mouse->
}*/










