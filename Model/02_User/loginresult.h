#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include "baseresult.h"

class LoginResult : public BaseResult
{
public:
    LoginResult();

public:
    long long id;
    QString username;
    QString passwd;
    QString encryptedpaswd;

    QString realname;
};

#endif // LOGINRESULT_H
