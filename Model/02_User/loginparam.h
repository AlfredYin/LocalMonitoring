#ifndef LOGINPARAM_H
#define LOGINPARAM_H

#include "baseparam.h"

class LoginParam : public BaseParam
{
public:
    LoginParam();

public:
    QString name;
    QString password;
};

#endif // LOGINPARAM_H
