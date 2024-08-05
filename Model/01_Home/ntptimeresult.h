#ifndef NTPTIMERESULT_H
#define NTPTIMERESULT_H

#include <QDateTime>

#include "baseresult.h"

class NtpTimeResult : public BaseResult
{
public:
    NtpTimeResult();

public:
    QDateTime ntpTime;

};

#endif // NTPTIMERESULT_H
