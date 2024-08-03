#ifndef USERHELPER_H
#define USERHELPER_H

#include "userinfo.h"

#include <QString>
#include <QMutex>

class UserHelper {
public:
    static UserHelper* instance();

    void setUserInfo(const UserInfo& info);
    UserInfo getUserInfo() const;

private:
    UserInfo userInfo_;

    UserHelper();
    ~UserHelper();

    UserHelper(const UserHelper&) = delete;
    UserHelper& operator=(const UserHelper&) = delete;
};

#endif // USERHELPER_H
