#include "svgreader.h"
#include <QPen>
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QStringList>
#include <QRect>
SvgReader::SvgReader()
{

}

QList<QGraphicsItem *> SvgReader::getElements(const QString filename)
{
    QList<QGraphicsItem *> itemList;    // Declare the stack list boxes

    QDomDocument doc;       // document object
    QFile file(filename);   // Open your SVG-file
    // If it is not opened, or have failed to transmit the contents in QDocDocument
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return itemList;    // the refund list, but empty

    // We are looking for all objects in a document with tag g
    QDomNodeList gList = doc.elementsByTagName("g");
    // Getting them to touch
    for (int i = 0; i < gList.size(); i++) {
        QDomNode gNode = gList.item(i);     // Select from the node list

        QDomNodeList objList = gNode.childNodes();
        for(int j = 0; j<objList.size(); j++)
        {
            QDomElement ele = objList.at(j).toElement();
            if(ele.tagName() == "rect"){
                QGraphicsRectItem *rect = new QGraphicsRectItem();
                // This flag makes the object moves, the need to test
                rect->setFlag(QGraphicsItem::ItemIsMovable);
                // Taking the dimensions of rect tag
                QDomElement gElement = gNode.toElement();
                rect->setRect(ele.attribute("x").toFloat(),
                              ele.attribute("y").toFloat(),
                              ele.attribute("width").toFloat(),
                              ele.attribute("height").toFloat());

                /* Take away from the element node gNode color options
                 * Yes yes yes ... because of gNode, instead of the rectangle. These parameters are stored in the tag g
                 * */
                QColor fillColor = Qt::black;
                //fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                rect->setBrush(QBrush(fillColor));

                QColor strokeColor = Qt::white;
                strokeColor.setAlphaF(0);


                itemList.append(rect);
            }
            else if (ele.tagName() == "ellipse")
            {
                QGraphicsEllipseItem *rect = new QGraphicsEllipseItem();
                // This flag makes the object moves, the need to test
                rect->setFlag(QGraphicsItem::ItemIsMovable);
                // Taking the dimensions of rect tag
                QDomElement gElement = gNode.toElement();
                float rx = ele.attribute("rx").toFloat();
                float ry = ele.attribute("ry").toFloat();
                float cx = ele.attribute("cx").toFloat();
                float cy = ele.attribute("cy").toFloat();
                rect->setRect(cx-rx, cy-ry, rx*2, ry*2);

                /* Take away from the element node gNode color options
                 * Yes yes yes ... because of gNode, instead of the rectangle. These parameters are stored in the tag g
                 * */
                QColor fillColor = Qt::black;
                //fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                rect->setBrush(QBrush(fillColor));

                QColor strokeColor = Qt::white;
                strokeColor.setAlphaF(0);


                itemList.append(rect);
            }
        }


    }
    file.close();
    return itemList;
}

QRectF SvgReader::getSizes(const QString filename)
{
    QDomDocument doc;       // initialize the stack object QDomDocument
    QFile file(filename);   // Open your SVG-file
    // If it is not opened, or have failed to transmit the contents in QDocDocument
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return QRectF(0,0,200,200); // the return values for the default scene

    /* Then pick up a list of items with the tag svg.
      * If a list of elements is not empty,
      * take the size of the graphic scenes.
     * */
    QDomNodeList list = doc.elementsByTagName("svg");
    if(list.length() > 0) {
        QDomElement svgElement = list.item(0).toElement();
        QStringList parameters = svgElement.attribute("viewBox").split(" ");
        return QRectF(parameters.at(0).toInt(),
                      parameters.at(1).toInt(),
                      parameters.at(2).toInt(),
                      parameters.at(3).toInt());
    }
    return QRectF(0,0,200,200);
}
