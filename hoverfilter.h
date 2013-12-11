#ifndef HOVERFILTER_H
#define HOVERFILTER_H

#include <QObject>
#include <QPushButton>
#include "mainwindow.h"

class HoverFilter : public QObject
{
    Q_OBJECT
public:
    explicit HoverFilter(QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QColor usualColor;

signals:

public slots:

};

#endif // HOVERFILTER_H
