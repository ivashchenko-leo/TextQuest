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
            if (this->gameWindow->pTimer->isActive()) {
                this->gameWindow->pTimer->stop();
                this->gameWindow->finishParagraph();
            } else {
                if (this->gameWindow->choiceNotExist) {
                    qDebug() << this->gameWindow->choiceNotExist;
                    this->gameWindow->tCount++;
                    if (!this->gameWindow->xmlDoc->isElementExist(this->gameWindow->scene, this->gameWindow->tCount)) {
                        this->gameWindow->sCount++;
                        if (!this->gameWindow->xmlDoc->isSceneExist(
                                    this->gameWindow->xmlDoc->getChapter(this->gameWindow->chapter),
                                    this->gameWindow->sCount)
                                ) {
                            this->gameWindow->chapter++;
                            if (!this->gameWindow->xmlDoc->isChapterExist(this->gameWindow->chapter)) {
                                return false;
                            }
                            this->gameWindow->sCount = 0;
                        }
                        this->gameWindow->setScene();
                        this->gameWindow->tCount = 0;
                    }
                    this->gameWindow->chooseAction(this->gameWindow->xmlDoc->getSceneElement(
                                                       this->gameWindow->scene,
                                                       this->gameWindow->tCount)
                                                   );
                }
            }
            return true;
        }
        if (((QMouseEvent*)event)->button() == Qt::RightButton) {
            return true;
        }
        if (((QMouseEvent*)event)->button() == Qt::MiddleButton) {
            return true;
        }
    }
    return false;
}
