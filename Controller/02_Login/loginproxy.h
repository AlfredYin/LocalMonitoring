#ifndef LOGINPROXY_H
#define LOGINPROXY_H

#include "loginparam.h"
#include "mysqldbrepository.h"
#include "Patterns/Proxy.h"

class LoginInfo;

// Model 代表应用程序的数据和业务逻辑。它通常由 Proxy 组成。
class LoginProxy : public Proxy , MySqlDBRepository
{
public:
    LoginProxy();

    void checkLogin(LoginParam *loginInfo);

    void changePwd(LoginParam *loginInfo);
};

#endif // LOGINPROXY_H
