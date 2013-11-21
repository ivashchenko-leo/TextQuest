#ifndef MOUSEFILTER_H
#define MOUSEFILTER_H

#include <QObject>
#include "gamewindow.h"

class GameWindow;

class MouseFilter : public QObject
{
    Q_OBJECT
public:
    explicit MouseFilter(QObject *parent = 0, GameWindow *window = 0);
    
protected:
    virtual bool eventFilter(QObject *, QEvent *event);

private:
    GameWindow *gameWindow;
    bool leftButtonClicked();
};

#endif // MOUSEFILTER_H
