#include "hoverfilter.h"

HoverFilter::HoverFilter(QObject *parent) :
    QObject(parent)
{
}

/*virtual*/
bool HoverFilter::eventFilter(QObject *obj, QEvent *event)
{
    QPalette palette;
    QPushButton *label;

    if (event->type() == QEvent::Enter) {
        label = qobject_cast<QPushButton*>(obj);
        palette = label->palette();
        this->usualColor = palette.color(QPalette::ButtonText);
        palette.setColor(label->foregroundRole(), QColor(Qt::cyan));
        label->setPalette(palette);

        return true;
    }

    if (event->type() == QEvent::Leave) {
        label = qobject_cast<QPushButton*>(obj);
        palette = label->palette();
        palette.setColor(label->foregroundRole(), this->usualColor);
        label->setPalette(palette);

        return true;
    }
    return false;
}
