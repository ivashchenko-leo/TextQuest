#include "settingsdialog.h"
#include "ui_settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    //ui->cbAutoRead->installEventFilter(new SettingsFilter(ui->cbAutoRead));
    connect(ui->pbOk, SIGNAL(clicked()), this, SLOT(acceptSettings()));
    connect(ui->tbColor, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(ui->tbFont, SIGNAL(clicked()), this, SLOT(changeFont()));
    //connect(ui->cbSkipUnreadText, SIGNAL(clicked(bool)), Settings::getInstance(), SLOT(setUnreadText(bool)));
    /*connect(ui->cbAutoRead, SIGNAL(clicked(bool)), Settings::getInstance(), SLOT(setAutoRead(bool)));
    connect(ui->cbSkipAfterChoice, SIGNAL(clicked(bool)), Settings::getInstance(), SLOT(setAfterChoice(bool)));
    connect(ui->cbFullScreen, SIGNAL(clicked(bool)), Settings::getInstance(), SLOT(setFullScreen(bool)));
    connect(ui->cbSound, SIGNAL(clicked(bool)), Settings::getInstance(), SLOT(setSound(bool)));*/
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::changeColor()
{
    QColor Color = QColorDialog::getColor(Settings::getInstance()->getTextColor(), this);
    if (Color.isValid())
    {
        Settings::getInstance()->setTextColor(Color);
        Settings::getInstance()->flush();
    }
}

void SettingsDialog::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, Settings::getInstance()->getFont(), this);

    if (ok)
    {
        Settings::getInstance()->setFont(font);
        Settings::getInstance()->flush();
    }
}

void SettingsDialog::acceptSettings()
{
    Settings::getInstance()->setSettings(Settings::FromUi, this);
    Settings::getInstance()->flush();
    this->accept();
}

void SettingsDialog::rejectSettings()
{
    this->reject();
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





















