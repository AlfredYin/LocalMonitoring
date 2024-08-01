#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include "Patterns/UpdateData.h"

class LoginResult : public UpdateData
{
public:
    LoginResult();

public:
    QString username;
    QString passwd;
    bool result;

    QString message;
};

#endif // LOGINRESULT_H
