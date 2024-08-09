#ifndef SCENEFILEHELPER_H
#define SCENEFILEHELPER_H

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QGraphicsPolygonItem>

#include <alfredgraphicsscene.h>
#include "devicerectitem.h"



class SceneFileHelper
{
public:
    SceneFileHelper();

    static bool saveSceneItemToFile(QString destPath,AlfredGraphicsScene* scene);

    static void loadItemToScene(AlfredGraphicsScene* scene,QString srcPath);
};

#endif // SCENEFILEHELPER_H
