#ifndef USERPROXY_H
#define USERPROXY_H

#include "loginparam.h"
#include "mysqldbrepository.h"
#include "Patterns/Proxy.h"
#include "userinfo.h"
#include "userparam.h"

#include <QRandomGenerator>
#include <QDateTime>

// Model 代表应用程序的数据和业务逻辑。它通常由 Proxy 组成。
class UserProxy : public Proxy , MySqlDBRepository
{
public:
    UserProxy();

    void checkLogin(LoginParam *loginParam);

    void changePwd(LoginParam *loginParam);

    UserInfo getUserInfo(UserParam *userParam);

private:
    QString EncryptUserPassword(QString password, QString salt);

    QString getPasswordSalt();

    UserInfo m_UserInfo;
};

#endif // USERPROXY_H
