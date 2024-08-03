#ifndef USERPARAM_H
#define USERPARAM_H

#include "baseparam.h"

class UserParam : BaseParam
{
public:
    UserParam();

public:
    QString username;
    QString passwd;

    QString realname;
};

#endif // USERPARAM_H
