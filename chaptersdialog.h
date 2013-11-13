#ifndef CHAPTERSDIALOG_H
#define CHAPTERSDIALOG_H

#include <QDialog>

namespace Ui {
class ChaptersDialog;
}

class ChaptersDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChaptersDialog(QWidget *parent = 0);
    ~ChaptersDialog();
    
private:
    Ui::ChaptersDialog *ui;
};

#endif // CHAPTERSDIALOG_H
