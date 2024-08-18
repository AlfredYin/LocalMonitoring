#ifndef HISTORYDATACOMMAND_H
#define HISTORYDATACOMMAND_H

#include "Command.h"
#include "dataproxy.h"
#include "sensorstateresult.h"
#include "sensorparam.h"

class HistoryDataCommand : public Command
{
public:
    HistoryDataCommand();

    void excute(INotification *notification);
};

#endif // HISTORYDATACOMMAND_H
