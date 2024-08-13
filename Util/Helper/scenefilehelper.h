#ifndef SCENEFILEHELPER_H
#define SCENEFILEHELPER_H

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDomDocument>

#include <QGraphicsPolygonItem>

#include <alfredgraphicsscene.h>
#include "devicerectitem.h"



class SceneFileHelper
{
public:
    SceneFileHelper();

    static bool saveSceneItemToFileJson(QString destPath,AlfredGraphicsScene* scene);

    static bool saveSceneItemToFileXml(QString destPath,AlfredGraphicsScene* scene);

    static void loadItemJsonToScene(AlfredGraphicsScene* scene,QString srcPath);

    static void loadItemXmlToScene(AlfredGraphicsScene* scene,QString srcPath);
};

#endif // SCENEFILEHELPER_H
