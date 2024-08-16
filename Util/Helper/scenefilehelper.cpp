#include "scenefilehelper.h"

SceneFileHelper::SceneFileHelper()
{

}

bool SceneFileHelper::saveSceneItemToFileXml(QString destPath, AlfredGraphicsScene *scene)
{
    QDomDocument doc;

    // 创建文档声明
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root=doc.createElement("SceneItems");
    doc.appendChild(root);

    foreach (QGraphicsItem* item, scene->items()) {
        if(item->type()==QGraphicsRectItem::Type){              // 矩形
            QDomElement itemElement=doc.createElement("Item");

            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(QGraphicsRectItem::Type)));
            itemElement.appendChild(nameElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();            
            QDomElement rectElement=doc.createElement("Rect");
            rectElement.setAttribute("x",QString::number(rect.x()));
            rectElement.setAttribute("y",QString::number(rect.y()));
            rectElement.setAttribute("width",QString::number(rect.width()));
            rectElement.setAttribute("height",QString::number(rect.height()));
            itemElement.appendChild(rectElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            QDomElement colorElement=doc.createElement("Color");
            colorElement.setAttribute("color_r",fillColor.red());
            colorElement.setAttribute("color_g",fillColor.green());
            colorElement.setAttribute("color_b",fillColor.blue());
            colorElement.setAttribute("color_a",fillColor.alpha());
            itemElement.appendChild(colorElement);

            root.appendChild(itemElement);
        }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

            QDomElement itemElement=doc.createElement("Item");

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(QGraphicsEllipseItem::Type)));
            itemElement.appendChild(nameElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();
            QDomElement rectElement=doc.createElement("Rect");
            rectElement.setAttribute("x",QString::number(rect.x()));
            rectElement.setAttribute("y",QString::number(rect.y()));
            rectElement.setAttribute("width",QString::number(rect.width()));
            rectElement.setAttribute("height",QString::number(rect.height()));
            itemElement.appendChild(rectElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            QDomElement colorElement=doc.createElement("Color");
            colorElement.setAttribute("color_r",fillColor.red());
            colorElement.setAttribute("color_g",fillColor.green());
            colorElement.setAttribute("color_b",fillColor.blue());
            colorElement.setAttribute("color_a",fillColor.alpha());
            itemElement.appendChild(colorElement);

            root.appendChild(itemElement);
        }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形

            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);

            // root子元素，Item的所有属性
            QDomElement itemElement=doc.createElement("Item");

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(QGraphicsPolygonItem::Type)));
            itemElement.appendChild(nameElement);


            // 保存多边形的点
            QDomElement polygonElement=doc.createElement("Polygon");
            QPolygonF polygon = theItem->polygon();
            for (const QPointF &point : polygon) {

                QDomElement lineElement=doc.createElement("Line");
                lineElement.setAttribute("x",QString::number(point.x()));
                lineElement.setAttribute("y",QString::number(point.y()));
                polygonElement.appendChild(lineElement);
            }
            itemElement.appendChild(polygonElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            QDomElement colorElement=doc.createElement("Color");
            colorElement.setAttribute("color_r",fillColor.red());
            colorElement.setAttribute("color_g",fillColor.green());
            colorElement.setAttribute("color_b",fillColor.blue());
            colorElement.setAttribute("color_a",fillColor.alpha());
            itemElement.appendChild(colorElement);

            root.appendChild(itemElement);
        }else if(item->type()==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);

            // root子元素，Item的所有属性
            QDomElement itemElement=doc.createElement("Item");

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(QGraphicsTextItem::Type)));
            itemElement.appendChild(nameElement);

            // 保存文字内容
            QDomElement textElement=doc.createElement("Text");
            // 将 theItem->toPlainText() 转换为 UTF-8 编码
            QString plainText = theItem->toPlainText();
            QByteArray utf8TextByte = plainText.toUtf8();

            textElement.appendChild(doc.createTextNode(QString::fromUtf8(utf8TextByte)));
            itemElement.appendChild(textElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 保存字体信息
            QFont font = theItem->font();
            QDomElement fontElement=doc.createElement("Font");
            fontElement.setAttribute("family",font.family());
            fontElement.setAttribute("pointSize",font.pointSize());
            fontElement.setAttribute("bold",font.bold());
            fontElement.setAttribute("italic",font.italic());
            fontElement.setAttribute("underline",font.underline());
            itemElement.appendChild(fontElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存文字颜色
            QColor fillColor = theItem->defaultTextColor();
            QDomElement colorElement=doc.createElement("Color");
            colorElement.setAttribute("color_r",fillColor.red());
            colorElement.setAttribute("color_g",fillColor.green());
            colorElement.setAttribute("color_b",fillColor.blue());
            colorElement.setAttribute("color_a",fillColor.alpha());
            itemElement.appendChild(colorElement);

            root.appendChild(itemElement);
        }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);

            // root子元素，Item的所有属性
            QDomElement itemElement=doc.createElement("Item");

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(SingleLineItem::Type)));
            itemElement.appendChild(nameElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 保存线条的起点和终点
            QPointF startPoint=theItem->getStartPoint();
            QPointF endPoint=theItem->getEndPoint();
            QDomElement lineElement=doc.createElement("Line");
            posElement.setAttribute("startpoint_x",QString::number(startPoint.x()));
            posElement.setAttribute("startpoint_y",QString::number(startPoint.y()));
            posElement.setAttribute("endpoint_x",QString::number(endPoint.x()));
            posElement.setAttribute("endpoint_y",QString::number(endPoint.y()));
            itemElement.appendChild(posElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存保存画笔相关信息
            QDomElement penElement=doc.createElement("Pen");

            QColor color = theItem->pen().color();
            penElement.setAttribute("color_r",color.red());
            penElement.setAttribute("color_g",color.green());
            penElement.setAttribute("color_b",color.blue());
            penElement.setAttribute("color_a",color.alpha());
            int width=theItem->pen().width();
            penElement.setAttribute("width",QString::number(width));
            itemElement.appendChild(penElement);

            root.appendChild(itemElement);
        }else if(item->type()==DeviceRectItem::Type){     // 设备模型
            DeviceRectItem *theItem;
            theItem=qgraphicsitem_cast<DeviceRectItem *>(item);

            // root子元素，Item的所有属性
            QDomElement itemElement=doc.createElement("Item");

            // 保存该图形的类型
            QDomElement nameElement=doc.createElement("Type");
            nameElement.appendChild(doc.createTextNode(QString::number(DeviceRectItem::Type)));
            itemElement.appendChild(nameElement);

            // 保存图形项的位置
            QPointF position = theItem->pos();
            QDomElement posElement=doc.createElement("Pos");
            posElement.setAttribute("pos_x",QString::number(position.x()));
            posElement.setAttribute("pos_y",QString::number(position.y()));
            posElement.setAttribute("pos_z",QString::number(theItem->zValue()));
            itemElement.appendChild(posElement);

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();
            QDomElement rectElement=doc.createElement("Rect");
            rectElement.setAttribute("x",QString::number(rect.x()));
            rectElement.setAttribute("y",QString::number(rect.y()));
            rectElement.setAttribute("width",QString::number(rect.width()));
            rectElement.setAttribute("height",QString::number(rect.height()));
            itemElement.appendChild(rectElement);

            // 缩放系数
            qreal scaleX = item->transform().m11(); // X方向的缩放系数
            qreal scaleY = item->transform().m22(); // Y方向的缩放系数
            QDomElement scaleElement=doc.createElement("Scale");
            scaleElement.setAttribute("x",QString::number(scaleX));
            scaleElement.setAttribute("y",QString::number(scaleY));
            itemElement.appendChild(scaleElement);

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            QDomElement colorElement=doc.createElement("Color");
            colorElement.setAttribute("color_r",fillColor.red());
            colorElement.setAttribute("color_g",fillColor.green());
            colorElement.setAttribute("color_b",fillColor.blue());
            colorElement.setAttribute("color_a",fillColor.alpha());
            itemElement.appendChild(colorElement);

            // 保存设备状态信息
            theItem->getDeviceStateInfo().toXml(doc, itemElement);

            root.appendChild(itemElement);
        }
    }

    QFile file(destPath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
//        stream<<doc.toString();;
        stream.setCodec("UTF-8"); // 设置编码为 UTF-8
        doc.save(stream, 4); // 保存 XML 文档
        file.close();
        return true;
    }else{
        return false;
    }
}

void SceneFileHelper::loadItemXmlToScene(AlfredGraphicsScene *scene, QString srcPath)
{
    QFile file(srcPath);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
//    QByteArray saveDate=file.readAll();
//    QJsonDocument jsonDoc(QJsonDocument::fromJson(saveDate));
//    QJsonArray jsonArray=jsonDoc.array();

    QDomDocument doc;
    if(!doc.setContent(&file)){
        qDebug()<<"Failed to parse XML .";
        file.close();
        return;
    }

    file.close();

    QDomElement root=doc.firstChildElement("SceneItems");
    QDomNodeList itemsNodes=root.elementsByTagName("Item");

    for(int i=0;i<itemsNodes.count();i++){

        QDomElement itemNode=itemsNodes.at(i).toElement();
        QDomElement typeNode=itemNode.firstChildElement("Type");
        int type=typeNode.text().toInt();

        if(type==QGraphicsRectItem::Type){              // 矩形

            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();


            QDomElement rectNode=itemNode.firstChildElement("Rect");
            int x=rectNode.attribute("x").toInt();
            int y=rectNode.attribute("y").toInt();
            int height=rectNode.attribute("height").toInt();
            int width=rectNode.attribute("width").toInt();

            QGraphicsRectItem *theItem=new QGraphicsRectItem(x,y,width,height);
            theItem->setPos(pos_x,pos_y);
            theItem->setZValue(pos_z);

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            theItem->setTransform(transform);

            QDomElement colorNode=itemNode.firstChildElement("Color");
            int red = colorNode.attribute("color_r").toInt();
            int green = colorNode.attribute("color_g").toInt();
            int blue = colorNode.attribute("color_b").toInt();
            int alpha = colorNode.attribute("color_a").toInt();
            QColor fillColor(red, green, blue, alpha);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
        }else if(type==QGraphicsEllipseItem::Type){     // 圆形，椭圆

            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();


            QDomElement rectNode=itemNode.firstChildElement("Rect");
            int x=rectNode.attribute("x").toInt();
            int y=rectNode.attribute("y").toInt();
            int height=rectNode.attribute("height").toInt();
            int width=rectNode.attribute("width").toInt();

            QGraphicsEllipseItem *theItem=new QGraphicsEllipseItem(x,y,width,height);
            theItem->setPos(pos_x,pos_y);
            theItem->setZValue(pos_z);

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            theItem->setTransform(transform);

            QDomElement colorNode=itemNode.firstChildElement("Color");
            int red = colorNode.attribute("color_r").toInt();
            int green = colorNode.attribute("color_g").toInt();
            int blue = colorNode.attribute("color_b").toInt();
            int alpha = colorNode.attribute("color_a").toInt();
            QColor fillColor(red, green, blue, alpha);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
        }else if(type==QGraphicsPolygonItem::Type){     // 多边形

            QGraphicsPolygonItem *theItem=new QGraphicsPolygonItem();

            // 加载多边形的点
            QDomElement polygonNode=itemNode.firstChildElement("Polygon");
            QDomNodeList lineNodes=polygonNode.elementsByTagName("Line");

            QPolygonF polygon;

            for(int i=0;i<lineNodes.count();i++){
                QDomElement lineNode=lineNodes.at(i).toElement();
                qreal x=lineNode.attribute("x").toInt();
                qreal y=lineNode.attribute("y").toInt();
                polygon << QPointF(x, y);
            }

            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();

            theItem->setPolygon(polygon);
            theItem->setPos(pos_x, pos_y);
            theItem->setZValue(pos_z);

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            theItem->setTransform(transform);

            QDomElement colorNode=itemNode.firstChildElement("Color");
            int red = colorNode.attribute("color_r").toInt();
            int green = colorNode.attribute("color_g").toInt();
            int blue = colorNode.attribute("color_b").toInt();
            int alpha = colorNode.attribute("color_a").toInt();
            QColor fillColor(red, green, blue, alpha);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
        }else if(type==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem = new QGraphicsTextItem();

            // 加载文字内容
            QDomElement textNode=itemNode.firstChildElement("Text");
            QString text=textNode.text();
            theItem->setPlainText(text);

            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();

            theItem->setPos(pos_x, pos_y);
            theItem->setZValue(pos_z);

            // 加载字体信息
            QDomElement fontNode=itemNode.firstChildElement("Font");
            QFont font;
            font.setFamily(fontNode.attribute("family"));
            font.setPointSize(fontNode.attribute("pointSize").toInt());
            font.setBold(fontNode.attribute("bold").toInt());
            font.setItalic(fontNode.attribute("italic").toInt());
            font.setUnderline(fontNode.attribute("underline").toInt());
            theItem->setFont(font);

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            theItem->setTransform(transform);

            QDomElement colorNode=itemNode.firstChildElement("Color");
            int red = colorNode.attribute("color_r").toInt();
            int green = colorNode.attribute("color_g").toInt();
            int blue = colorNode.attribute("color_b").toInt();
            int alpha = colorNode.attribute("color_a").toInt();
            QColor color(red, green, blue, alpha);

            theItem->setDefaultTextColor(color);

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);

        }else if(type==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem=new SingleLineItem();

            // 加载线条的起点和终点和位置
            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();
            int endpoint_x=posNode.attribute("endpoint_x").toInt();
            int endpoint_y=posNode.attribute("endpoint_y").toInt();
            int startpoint_x=posNode.attribute("startpoint_x").toInt();
            int startpoint_y=posNode.attribute("startpoint_y").toInt();


            theItem->setStartPoint(QPointF(startpoint_x,startpoint_y));
            theItem->setEndPoint(QPointF(endpoint_x,endpoint_y));

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            theItem->setTransform(transform);

            // 加载线条的颜色
            QPen pen = theItem->pen();
            QDomElement penNode=itemNode.firstChildElement("Pen");
            int red = penNode.attribute("color_r").toInt();
            int green = penNode.attribute("color_g").toInt();
            int blue = penNode.attribute("color_b").toInt();
            int alpha = penNode.attribute("color_a").toInt();
            int width=penNode.attribute("width").toInt();
            QColor color(red, green, blue, alpha);

            // 加载线条的宽度
            pen.setWidth(width);
            pen.setColor(color);
            theItem->setPen(pen);

            theItem->setPos(pos_x, pos_y);
            theItem->setZValue(pos_z);

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
//            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        }else if(type==DeviceRectItem::Type){     // 设备模型
            // 加载设备矩形的位置

            QDomElement posNode=itemNode.firstChildElement("Pos");
            int pos_x=posNode.attribute("pos_x").toInt();
            int pos_y=posNode.attribute("pos_y").toInt();
            int pos_z=posNode.attribute("pos_z").toInt();


            QDomElement rectNode=itemNode.firstChildElement("Rect");
            int x=rectNode.attribute("x").toInt();
            int y=rectNode.attribute("y").toInt();
            int height=rectNode.attribute("height").toInt();
            int width=rectNode.attribute("width").toInt();

            DeviceRectItem *deviceItem=new DeviceRectItem(x,y,width,height);

            deviceItem->setPos(pos_x,pos_y);
            deviceItem->setZValue(pos_z);

            QDomElement scaleNode = itemNode.firstChildElement("Scale");
            qreal scaleX = scaleNode.attribute("x").toDouble();
            qreal scaleY = scaleNode.attribute("y").toDouble();
            QTransform transform;
            transform.scale(scaleX,scaleY); // 设置X方向缩放系数为1.5，Y方向缩放系数为2.0
            deviceItem->setTransform(transform);

            QDomElement colorNode=itemNode.firstChildElement("Color");
            // 设备矩形的颜色
            int red = colorNode.attribute("color_r").toInt();
            int green = colorNode.attribute("color_g").toInt();
            int blue = colorNode.attribute("color_b").toInt();
            int alpha = colorNode.attribute("color_a").toInt();
            QColor fillColor(red, green, blue, alpha);
            deviceItem->setBrush(QBrush(fillColor));


            // 加载内部矩形的设备数据
            DeviceStateInfo deviceStateInfo;
            QDomNodeList deviceNodes = itemNode.elementsByTagName("DeviceStateInfo");
            if (!deviceNodes.isEmpty()) {
                deviceStateInfo.fromXml(deviceNodes.at(0).toElement());
            }
            deviceItem->setDeviceStateInfo(deviceStateInfo);

            deviceItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(deviceItem);
        }
    }
}

bool SceneFileHelper::saveSceneItemToFileJson(QString destPath, AlfredGraphicsScene *scene)
{

    QJsonArray jsonArray;

    foreach (QGraphicsItem* item, scene->items()) {

        if(item->type()==QGraphicsRectItem::Type){              // 矩形

            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
            QJsonObject jsonObject;

            // 保存该图形的类型
            jsonObject["type"]=QGraphicsRectItem::Type;

            // 保存图形项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();
            jsonObject["x"] = rect.x();
            jsonObject["y"] = rect.y();
            jsonObject["width"] = rect.width();
            jsonObject["height"] = rect.height();

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            jsonObject["color_r"] = fillColor.red();
            jsonObject["color_g"] = fillColor.green();
            jsonObject["color_b"] = fillColor.blue();
            jsonObject["color_a"] = fillColor.alpha();

            jsonArray.append(jsonObject);

        }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem;

            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
            QJsonObject jsonObject;

            // 保存该图形的类型
            jsonObject["type"]=QGraphicsEllipseItem::Type;

            // 保存图形项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();
            jsonObject["x"] = rect.x();
            jsonObject["y"] = rect.y();
            jsonObject["width"] = rect.width();
            jsonObject["height"] = rect.height();

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            jsonObject["color_r"] = fillColor.red();
            jsonObject["color_g"] = fillColor.green();
            jsonObject["color_b"] = fillColor.blue();
            jsonObject["color_a"] = fillColor.alpha();

            jsonArray.append(jsonObject);
        }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形
            QJsonObject jsonObject;

            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);

            jsonObject["type"]=QGraphicsPolygonItem::Type;
            // 保存多边形的点
            QPolygonF polygon = theItem->polygon();
            QJsonArray pointsArray;
            for (const QPointF &point : polygon) {
                QJsonObject pointObject;
                pointObject["x"] = point.x();
                pointObject["y"] = point.y();
                pointsArray.append(pointObject);
            }
            jsonObject["points"] = pointsArray;

            // 保存图形项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            jsonObject["color_r"] = fillColor.red();
            jsonObject["color_g"] = fillColor.green();
            jsonObject["color_b"] = fillColor.blue();
            jsonObject["color_a"] = fillColor.alpha();

            jsonArray.append(jsonObject);

        }else if(item->type()==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);
            QJsonObject jsonObject;

            jsonObject["type"]=QGraphicsTextItem::Type;
            // 保存文字内容
            jsonObject["text"] = theItem->toPlainText();

            // 保存文字项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存字体信息
            QFont font = theItem->font();
            QJsonObject fontObject;
            fontObject["family"] = font.family();
            fontObject["pointSize"] = font.pointSize();
            fontObject["bold"] = font.bold();
            fontObject["italic"] = font.italic();
            fontObject["underline"] = font.underline();
            jsonObject["font"] = fontObject;

            // 保存文字颜色
            QColor color = theItem->defaultTextColor();
            jsonObject["color_r"] = color.red();
            jsonObject["color_g"] = color.green();
            jsonObject["color_b"] = color.blue();
            jsonObject["color_a"] = color.alpha();

            jsonArray.append(jsonObject);
        }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);

            QJsonObject jsonObject;
            jsonObject["type"]=SingleLineItem::Type;

            // 保存文字项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存线条的起点和终点
            QPointF startPoint=theItem->getStartPoint();
            jsonObject["startpoint_x"] = startPoint.x();
            jsonObject["startpoint_y"] = startPoint.y();

            QPointF endPoint=theItem->getEndPoint();
            jsonObject["endpoint_x"] = endPoint.x();
            jsonObject["endpoint_y"] = endPoint.y();

            // 保存线条的颜色
            QColor color = theItem->pen().color();
            jsonObject["color_r"] = color.red();
            jsonObject["color_g"] = color.green();
            jsonObject["color_b"] = color.blue();
            jsonObject["color_a"] = color.alpha();

            // 保存线条的宽度
            jsonObject["pen_width"] = theItem->pen().width();
            jsonArray.append(jsonObject);

        }else if(item->type()==DeviceRectItem::Type){     // 设备模型
            DeviceRectItem *theItem;
            theItem=qgraphicsitem_cast<DeviceRectItem *>(item);
            QJsonObject jsonObject;

            jsonObject["type"]=DeviceRectItem::Type;

            // 保存图形项的位置
            QPointF position = theItem->pos();
            jsonObject["pos_x"] = position.x();
            jsonObject["pos_y"] = position.y();

            // 保存矩形的几何信息
            QRectF rect = theItem->rect();
            jsonObject["x"] = rect.x();
            jsonObject["y"] = rect.y();
            jsonObject["width"] = rect.width();
            jsonObject["height"] = rect.height();

            // 保存填充颜色
            QColor fillColor = theItem->brush().color();
            jsonObject["color_r"] = fillColor.red();
            jsonObject["color_g"] = fillColor.green();
            jsonObject["color_b"] = fillColor.blue();
            jsonObject["color_a"] = fillColor.alpha();

            // 保存设备状态信息 (假设 `DeviceStateInfo` 有 `toJson` 方法)
            QJsonObject stateInfoObject = theItem->getDeviceStateInfo().toJson();
            jsonObject["deviceStateInfo"] = stateInfoObject;

            jsonArray.append(jsonObject);
        }
    }

    QJsonDocument jsonDoc(jsonArray);
    QFile file(destPath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        return true;
    }else{
        return false;
    }
}

void SceneFileHelper::loadItemJsonToScene(AlfredGraphicsScene *scene,QString srcPath)
{
    QFile file(srcPath);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    QByteArray saveDate=file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(saveDate));
    QJsonArray jsonArray=jsonDoc.array();



    for(const QJsonValue &value:jsonArray){
        int type=value["type"].toInt();
        QJsonObject jsonObject=value.toObject();

        // 加载矩形的信息
        qreal x=jsonObject["x"].toDouble();
        qreal y=jsonObject["y"].toDouble();
        qreal width=jsonObject["width"].toDouble();
        qreal height=jsonObject["height"].toDouble();

        qreal posX=jsonObject["pos_x"].toDouble();
        qreal posY=jsonObject["pos_y"].toDouble();

        int red = jsonObject["color_r"].toInt();
        int green = jsonObject["color_g"].toInt();
        int blue = jsonObject["color_b"].toInt();
        int alpha = jsonObject["color_a"].toInt();
        QColor fillColor(red, green, blue, alpha);

        if(type==QGraphicsRectItem::Type){              // 矩形
            QGraphicsRectItem *theItem=new QGraphicsRectItem(x,y,width,height);
            theItem->setPos(posX,posY);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);

        }else if(type==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem=new QGraphicsEllipseItem(x,y,width,height);
            theItem->setPos(posX,posY);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
        }else if(type==QGraphicsPolygonItem::Type){     // 多边形
            QGraphicsPolygonItem *theItem=new QGraphicsPolygonItem();
            // 加载多边形的点
            QJsonArray pointsArray = jsonObject["points"].toArray();
            QPolygonF polygon;
            for (const QJsonValue &value : pointsArray) {
                QJsonObject pointObject = value.toObject();
                qreal x = pointObject["x"].toDouble();
                qreal y = pointObject["y"].toDouble();
                polygon << QPointF(x, y);
            }

            theItem->setPolygon(polygon);
            theItem->setPos(posX, posY);
            theItem->setBrush(QBrush(fillColor));

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);
        }else if(type==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem = new QGraphicsTextItem();
            // 加载文字内容
            QString text = jsonObject["text"].toString();
            theItem->setPlainText(text);
            theItem->setPos(posX, posY);

            // 加载字体信息
            QJsonObject fontObject = jsonObject["font"].toObject();
            QFont font;
            font.setFamily(fontObject["family"].toString());
            int pointSize = fontObject["pointSize"].toInt();
            if (pointSize <= 0) {
                pointSize = 12; // 设置一个默认值
            }

            font.setPointSize(pointSize);
            font.setBold(fontObject["bold"].toBool());
            font.setItalic(fontObject["italic"].toBool());
            font.setUnderline(fontObject["underline"].toBool());
            theItem->setFont(font);

            theItem->setDefaultTextColor(Qt::black);

            theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(theItem);

        }else if(type==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem=new SingleLineItem();
            // 加载线条的起点和终点
                qreal x1 = jsonObject["startpoint_x"].toDouble();
                qreal y1 = jsonObject["startpoint_y"].toDouble();

                qreal x2 = jsonObject["endpoint_x"].toDouble();
                qreal y2 = jsonObject["endpoint_y"].toDouble();

                theItem->setStartPoint(QPointF(x1,y1));
                theItem->setEndPoint(QPointF(x2,y2));
                // 加载线条的颜色
                QPen pen = theItem->pen();
                pen.setColor(fillColor);
                theItem->setPen(pen);

                theItem->setPos(posX, posY);

                // 加载线条的宽度
                int penWidth = jsonObject["pen_width"].toInt();
                pen.setWidth(penWidth);
                theItem->setPen(pen);

                theItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);

                scene->addItem(theItem);
//            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        }else if(type==DeviceRectItem::Type){     // 设备模型
            // 加载设备矩形的位置
            DeviceRectItem *deviceItem=new DeviceRectItem(x,y,width,height);
            deviceItem->setPos(posX,posY);
            // 设备矩形的颜色
            deviceItem->setBrush(QBrush(fillColor));

            // 加载内部矩形的设备数据
            QJsonObject stateInfoObject=jsonObject["deviceStateInfo"].toObject();
            DeviceStateInfo stateInfo;
            stateInfo.fromJson(stateInfoObject);
            deviceItem->setDeviceStateInfo(stateInfo);

            deviceItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                           QGraphicsRectItem::ItemIsSelectable |
                           QGraphicsRectItem::ItemIsMovable);

            scene->addItem(deviceItem);
        }
    }
}
