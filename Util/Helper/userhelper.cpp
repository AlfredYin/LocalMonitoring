#include "userhelper.h"

#include <QMutexLocker>
#include <QMutex>

// 单例实例指针
static UserHelper* userHelperInstance = nullptr;

UserHelper* UserHelper::instance()
{
    if (userHelperInstance == nullptr) {
        if (userHelperInstance == nullptr) {
            userHelperInstance = new UserHelper();
        }
    }
    return userHelperInstance;
}

UserHelper::UserHelper()
{
    // 默认初始化 UserInfo
    // 在构造函数中可以进行额外的初始化
}

UserHelper::~UserHelper()
{
    // 清理资源
}

void UserHelper::setUserInfo(const UserInfo& info)
{
    userInfo_ = info;
}

UserInfo UserHelper::getUserInfo() const
{
    UserInfo result = userInfo_;
    return result;
}
