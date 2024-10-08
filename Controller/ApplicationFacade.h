#ifndef APPLICATIONFACADE_H
#define APPLICATIONFACADE_H

#include "Facade.h"
#include "mainwindowmediator.h"

class ApplicationFacade : public Facade
{
public:
    ApplicationFacade();

protected:
    void initializeMediator();
    void initializeCommand();
    void initializeProxy();
};

#endif // APPLICATIONFACADE_H
