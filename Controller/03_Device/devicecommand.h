#ifndef DEVICECOMMAND_H
#define DEVICECOMMAND_H

#include "Patterns/Command.h"

class DeviceCommand : public Command
{
public:
    DeviceCommand();

    void excute(INotification *notification);
};

#endif // DEVICECOMMAND_H
