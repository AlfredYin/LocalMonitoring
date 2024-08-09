#include "scenefilehelper.h"

SceneFileHelper::SceneFileHelper()
{

}

bool SceneFileHelper::saveSceneItemToFile(QString destPath, AlfredGraphicsScene *scene)
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

void SceneFileHelper::loadItemToScene(AlfredGraphicsScene *scene,QString srcPath)
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
