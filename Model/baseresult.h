#ifndef BASERESULT_H
#define BASERESULT_H

#include "UpdateData.h"

class BaseResult : public UpdateData
{
public:
    bool result;
    QString message;
};

#endif // BASERESULT_H
