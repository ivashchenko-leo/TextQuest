#include "chaptersdialog.h"
#include "ui_chaptersdialog.h"

ChaptersDialog::ChaptersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChaptersDialog)
{
    ui->setupUi(this);
}

ChaptersDialog::~ChaptersDialog()
{
    delete ui;
}
