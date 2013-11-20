#ifndef CHOICEFILTER_H
#define CHOICEFILTER_H

#include <QObject>
#include "gamewindow.h"

class GameWindow;

class ChoiceFilter : public QObject
{
    Q_OBJECT
public:
    explicit ChoiceFilter(QObject *parent = 0, GameWindow *window = 0);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    
private:
    GameWindow *gameWindow;

};

#endif // CHOICEFILTER_H
