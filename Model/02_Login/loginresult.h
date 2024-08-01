#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include "baseresult.h"

class LoginResult : public BaseResult
{
public:
    LoginResult();

public:
    QString username;
    QString passwd;
};

#endif // LOGINRESULT_H
