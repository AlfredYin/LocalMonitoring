#ifndef HOMEPROXY_H
#define HOMEPROXY_H

#include "databaserepository.h"
#include "Proxy.h"
#include "userparam.h"
#include "userinfo.h"

#include <QRandomGenerator>
#include <QDateTime>

class HomeProxy: public Proxy , DataBaseRepository
{
public:
    HomeProxy();

    void saveUser(UserInfo *userInfo);
};

#endif // HOMEPROXY_H
