#ifndef SCENEFILEHELPER_H
#define SCENEFILEHELPER_H

#include <QString>
#include <alfredgraphicsscene.h>

class SceneFileHelper
{
public:
    SceneFileHelper();

    static void loadItemToScene(AlfredGraphicsScene* Scene, bool bIsDialog, QString srcPath);
};

#endif // SCENEFILEHELPER_H
