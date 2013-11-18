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
                this->gameWindow->pCount++;
                if (!this->gameWindow->xmlDoc->isPExist(this->gameWindow->scene, this->gameWindow->pCount)) {
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
                    this->gameWindow->pCount = 0;
                }
                this->gameWindow->showParagraph(
                            this->gameWindow->xmlDoc->getP(this->gameWindow->scene,
                                                           this->gameWindow->pCount)
                            );
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
