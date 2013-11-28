#include "choicefilter.h"

ChoiceFilter::ChoiceFilter(QObject *parent, GameWindow *window) :
    QObject(parent)
{
    this->gameWindow = window;
}

/*virtual*/
bool ChoiceFilter::eventFilter(QObject *obj, QEvent *event)
{
    QDomNode choiceNode;
    if (event->type() == QEvent::MouseButtonPress) {
        if (((QMouseEvent*)event)->button() == Qt::LeftButton) {
            choiceNode = this->gameWindow->xmlDoc->getChoiceList(this->gameWindow->scene)
                    .at(obj->objectName().toInt());
            if (!choiceNode.toElement().attribute("file").isEmpty()) {
                this->gameWindow->setNewFile(choiceNode.toElement().attribute("file"));
            }
            this->gameWindow->sceneId = choiceNode.toElement().attribute("scene");
            this->gameWindow->choiceNotExist = true;
            this->gameWindow->setScene();
            return true;
        }
    }
    return false;
}
