#ifndef HOMENTPTIMECOMMAND_H
#define HOMENTPTIMECOMMAND_H

#include "Command.h"

class HomeNtpTimeCommand : public Command
{
public:
    HomeNtpTimeCommand();

    void excute(INotification *notification);

private:
    void on_TimeoutGetNetTime();

};

#endif // HOMENTPTIMECOMMAND_H
