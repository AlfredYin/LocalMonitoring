#ifndef DEVICESTATELISTCOMMAND_H
#define DEVICESTATELISTCOMMAND_H

#include "Command.h"

#include "Facade.h"
#include "INotification.h"
#include <QtConcurrent/QtConcurrent>

class DeviceStateListCommand : public Command
{
public:
    DeviceStateListCommand();

    void excute(INotification *notification);
};

#endif // DEVICESTATELISTCOMMAND_H
