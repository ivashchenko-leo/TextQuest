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
            QString objName;

            if (this->gameWindow->getWidgetOnCoord(((QMouseEvent*)event)->pos()) != 0) {
                objName = this->gameWindow->getWidgetOnCoord(((QMouseEvent*)event)->pos())->objectName();
            } else {
                objName = "other";
            }

            QRegExp reg("^[0-9][0-9]?$");

            if (reg.indexIn(objName) != -1) {
                return this->choiceClicked(objName);
            } else {
                return this->leftButtonClicked();
            }
        } else {
            return false;
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

bool MouseFilter::choiceClicked(QString objectName)
{
    QDomNode choiceNode;
    choiceNode = this->gameWindow->xmlDoc->getChoiceList(this->gameWindow->scene)
            .at(objectName.toInt());

    if (!choiceNode.toElement().attribute("file").isEmpty()) {
        this->gameWindow->setNewFile(choiceNode.toElement().attribute("file"));
    }
    this->gameWindow->sceneId = choiceNode.toElement().attribute("scene");
    this->gameWindow->choiceNotExist = true;
    this->gameWindow->setScene();
    this->gameWindow->sendLeftClick();

    return true;
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
