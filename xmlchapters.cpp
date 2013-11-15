#include "xmlchapters.h"

XmlChapters::XmlChapters():
    QXmlDefaultHandler ()
{

}

bool XmlChapters::startElement(const QString &,
                  const QString &,
                  const QString &qName,
                  const QXmlAttributes &atts)
{
    int count;

    count = atts.count();
    if (qName == GameMenu::GameTag) {
        for (int i = 0; i < count; i++) {
            if (atts.localName(i) == "name") {
                if (this->gameName.isEmpty())
                    this->gameName = atts.value(i);
                qDebug() << "Game name: " << atts.value(i);
            }
        }
    }
    if (qName == GameMenu::ChapterTag) {
        for (int i = 0; i < count; i++) {
            if (atts.localName(i) == "name") {
                this->currentChapter = atts.value(i);
                qDebug() << "Chapter name: " << atts.value(i);
            }
        }
    }
    if (qName == GameMenu::SceneTag) {
        for (int i = 0; i < count; i++) {
            if (atts.localName(i) == "id") {
                this->currentScene = atts.value(i);
                this->gameTree.insert(this->currentChapter, this->currentScene);
                qDebug() << "Scene id: " << atts.value(i);
            }
        }
    }
    return true;
}

QString XmlChapters::getGameName()
{
    return this->gameName;
}

bool XmlChapters::characters(const QString &ch)
{
    this->tagValue = ch;
    return true;
}

bool XmlChapters::endElement(const QString &,
                             const QString &,
                             const QString &qName)
{
    if (qName == GameMenu::IconTag) {
        this->chaptersIcon.insert(this->currentChapter, this->tagValue);
        qDebug() << "Icon: " << this->tagValue;
    }
    if (qName == GameMenu::ImageTag) {
        this->scenesImg.insert(this->currentScene, this->tagValue);
        qDebug() << "Image: " << this->tagValue;
    }
    return true;
}

bool XmlChapters::fatalError(const QXmlParseException &exception)
{
    QString message = "Line: %1\n Column: %2\n %3";
    message.arg(QString::number(exception.lineNumber()),
                QString::number(exception.columnNumber()),
                exception.message());
    QMessageBox::critical(0, QCoreApplication::tr("Error!"), message);
    return false;
}
