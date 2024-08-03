#ifndef HOMEPROXY_H
#define HOMEPROXY_H

#include "mysqldbrepository.h"
#include "Proxy.h"
#include "userparam.h"
#include "userinfo.h"

#include <QRandomGenerator>
#include <QDateTime>

class HomeProxy: public Proxy , MySqlDBRepository
{
public:
    HomeProxy();

    void saveUser(UserInfo *userInfo);
};

#endif // HOMEPROXY_H
