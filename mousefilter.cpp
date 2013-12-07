#include "mousefilter.h"

MouseFilter::MouseFilter(QObject *parent, GameWindow *window) :
    QObject(parent)
{
    this->gameWindow = window;
}

/*virtual*/
bool MouseFilter::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (((QMouseEvent*)event)->button() == Qt::LeftButton) {
            return this->leftButtonClicked();
        } else {
            if (((QMouseEvent*)event)->button() == Qt::RightButton) {
                qDebug() << "Right click";
                return true;
            } else {
                if (((QMouseEvent*)event)->button() == Qt::MiddleButton) {
                    return true;
                }
            }
        }
    } else {
        if (event->type() == QEvent::MouseButtonDblClick) {
            if (((QMouseEvent*)event)->button() == Qt::LeftButton) {
                return this->leftButtonClicked();
            }
        }
    }
    return false;
}

bool MouseFilter::leftButtonClicked()
{
    if (this->gameWindow->pTimer->isActive()) {
        this->gameWindow->pTimer->stop();
        this->gameWindow->finishParagraph();
    } else {
        if (this->gameWindow->choiceNotExist) {
            this->gameWindow->tCount++;
            if (!this->gameWindow->xmlDoc->isElementExist(this->gameWindow->scene, this->gameWindow->tCount)) {
                this->gameWindow->sceneId = QString::number(this->gameWindow->sceneId.toInt() + 1);
                this->gameWindow->setScene();
                this->gameWindow->setChapter();
                this->gameWindow->tCount = 0;
            }
            this->gameWindow->chooseAction(this->gameWindow->xmlDoc->getSceneElement(
                                               this->gameWindow->scene,
                                               this->gameWindow->tCount)
                                           );
            return true;
        }
        return false;
    }
    return true;
}
