#include "settingsdialog.h"
#include "ui_settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->pbOk, SIGNAL(clicked()), this, SLOT(acceptSettings()));
    connect(ui->tbColor, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(ui->tbFont, SIGNAL(clicked()), this, SLOT(changeFont()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::changeColor()
{
    QColor Color = QColorDialog::getColor(Qt::lightGray, this);

    if (Color.isValid())
    {

    }
}

void SettingsDialog::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);

    if (ok)
    {

    }
}

void SettingsDialog::acceptSettings()
{
    this->accept();
}
