#ifndef USERINFO_H
#define USERINFO_H

#include "baseinfo.h"

#include <QString>

class UserInfo : BaseInfo
{
public:
    UserInfo();

public:
    long id;

    QString username;
    QString passwd;

    QString realname;
};

#endif // USERINFO_H
