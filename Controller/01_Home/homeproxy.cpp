#include "homeproxy.h"
#include "userhelper.h"

#include "userhelper.h"
#include <QDebug>

HomeProxy::HomeProxy()
{

}

void HomeProxy::saveUser(UserInfo *userInfo)
{
    UserHelper* userHelper = UserHelper::instance();
    userHelper->setUserInfo(*userInfo);
}
