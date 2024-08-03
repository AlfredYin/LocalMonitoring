#include "UserProxy.h"

#include "loginresult.h"
#include "changepwdresult.h"
#include "loginparam.h"

#include "mysqldbmanager.h"
#include "queryhandler.h"
#include "securityhelper.h"
#include "userhelper.h"

#include <QThread>

// 初始化名称
UserProxy::UserProxy()
{
    PROXY_NAME = "UserProxy";
}

// 处理真正的业务逻辑和数据操作。可以作为数据模型的抽象层，与数据库或其他数据源交互。
void UserProxy::checkLogin(LoginParam *loginParam)
{
    UserHelper* userHelper = UserHelper::instance();
    UserInfo userInfo;
    userInfo.username=loginParam->name;
    userInfo.passwd=loginParam->password;
    userHelper->setUserInfo(userInfo);

//    userHelper->getUserInfo().username=loginParam->name;
//    userHelper->getUserInfo().passwd=loginParam->password;

//    userInfo.passwd = loginParam->password;
//    QString passwd = loginParam->password;

    QString queryStr="SELECT id,UserName,RealName,Password, Salt FROM SysUser Where UserName=:username";
//    QSqlQuery query=executeQuery(queryStr,{{":username",loginParam->name}});  // 同步方法获取数据

    QueryHandler *handler=new QueryHandler(this);
    QList<QPair<QString, QVariant>> bindValues = {
        { ":username", loginParam->name}
    };
//    QString username = userHelper->getUserInfo().username;
//    handler.startQuery(queryStr,{{":username",loginParam->name}});


    QObject::connect(handler, &QueryHandler::queryFinished, [this](QSqlQuery query) {

        LoginResult *loginResult = new LoginResult();
        loginResult->result = false;
        if(query.first()){
            float id = query.value(0).toFloat();

            QString username = query.value(1).toString();
            QString realname = query.value(2).toString();
            QString password = query.value(3).toString();
            QString salt = query.value(4).toString();

            UserHelper* userHelper = UserHelper::instance();
            if(password==EncryptUserPassword(userHelper->getUserInfo().passwd,salt)){
                loginResult->result = true;
                loginResult->username=username;
                loginResult->realname=realname;
                loginResult->passwd=userHelper->getUserInfo().passwd;
            }
        }else{
            loginResult->result = false;
        }

        sendNotification("login_finished", (void *)loginResult);
    });

    handler->startQuery(queryStr,bindValues);

//    return false;
//QThread::sleep(10);

//    // 发送成功的通知
//    sendNotification("login_finished", (void *)loginResult);
//    return loginResult->result;
}

void UserProxy::changePwd(LoginParam *loginInfo)
{
    ChangePwdResult *changePwdResult = new ChangePwdResult();

    QString name = loginInfo->name;
    QString passwd = loginInfo->password;

    QString queryStr="SELECT id,UserName, Password, Salt FROM SysUser";
    QSqlQuery query=executeQuery(queryStr);

    changePwdResult->result = true;
    if(query.first()) {

//        float id = query.value(0).toFloat();
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        QString salt = query.value(3).toString();

        if(name==username){
            if(password==EncryptUserPassword(passwd,salt)){
                changePwdResult->result = false;
                changePwdResult->message = "新密码与老密码相同";
            }
        }
    }else{
        changePwdResult->result = false;
        changePwdResult->message = "系统中不存在该用户";
    }


    // 随机生产密码盐 根据修改的密码重新生产
    if(changePwdResult->result){

        QString salt=getPasswordSalt();
        QString passWord=EncryptUserPassword(passwd,salt);

        QString queryChangePwdStr="UPDATE `AlfredDb`.`SysUser` SET Password=:passwd,Salt=:salt WHERE UserName=:user;";
        QSqlQuery query=executeQuery(queryChangePwdStr,{{":passwd",passWord},{":salt",salt},{":user",name}});

//        QSqlQuery query=executeQuery("UPDATE `AlfredDb`.`SysUser` SET Password=:passwd,Salt=:salt WHERE UserName=:user;",
//                                        {{":passwd","passWord"},{":salt","salt"},{":user","admin"}});

        if(query.numRowsAffected()>0){
            changePwdResult->result = true;
        }else{
            changePwdResult->result = false;
            changePwdResult->message = "query.numRowsAffected()==0";
        }
    }

    sendNotification("change_passwd_finished", (void *)changePwdResult);
}

UserInfo UserProxy::getUserInfo(UserParam *userParam)
{
    UserInfo userInfo = UserInfo();

    QString name = userParam->username;

    QString queryStr="SELECT id,UserName,RealName,Password, Salt FROM SysUser Where UserName=:username";
    QSqlQuery query=executeQuery(queryStr,{{":username",name}});

    if(query.first()){
        userInfo.id=query.value(0).toFloat();
        userInfo.username=query.value(1).toString();
        userInfo.realname=query.value(2).toString();
        userInfo.passwd=query.value(3).toString();

    }else{
        userInfo.id=-1;
        return userInfo;
    }

    return userInfo;
}

/*
void example1()
{
    // 使用位置绑定
    QSqlQuery query = db.executeQuery("SELECT * FROM users WHERE id = ? AND email = ?", {1, "test@example.com"});
    while (query.next())
    {
        qDebug() << "ID:" << query.value(0).toInt();
        qDebug() << "Username:" << query.value(1).toString();
        qDebug() << "Email:" << query.value(2).toString();
    }
}

void example2()
{
    // 使用名称绑定
    QSqlQuery query = db.executeQuery("SELECT * FROM users WHERE id = :id AND email = :email",
                                     {{"id", 1}, {"email", "test@example.com"}});
    while (query.next())
    {
        qDebug() << "ID:" << query.value(0).toInt();
        qDebug() << "Username:" << query.value(1).toString();
        qDebug() << "Email:" << query.value(2).toString();
    }
}

void example3()
{
    // 使用初始化列表按名称绑定
    QSqlQuery query = db.executeQuery("SELECT * FROM users WHERE id = :id AND email = :email",
                                     {{"id", 1}, {"email", "test@example.com"}});
    while (query.next())
    {
        qDebug() << "ID:" << query.value(0).toInt();
        qDebug() << "Username:" << query.value(1).toString();
        qDebug() << "Email:" << query.value(2).toString();
    }
}

void example4()
{
    // 使用位置绑定 - 插入数据
    QSqlQuery query = db.executeQuery("INSERT INTO posts (title, content, user_id) VALUES (?, ?, ?)",
                                     {"My First Post", "This is my first post on this blog.", 1});
    if (query.lastInsertId().isValid())
    {
        qDebug() << "New post ID:" << query.lastInsertId().toInt();
    }
}

void example5()
{
    // 使用名称绑定 - 更新数据
    QSqlQuery query = db.executeQuery("UPDATE posts SET title = :title, content = :content WHERE id = :id",
                                     {{"title", "Updated Title"}, {"content", "Updated Content"}, {"id", 1}});
    if (query.numRowsAffected() > 0)
    {
        qDebug() << "Updated successfully.";
    }
}
*/

QString UserProxy::EncryptUserPassword(QString password, QString salt)
{

    QString md5Password = SecurityHelper::md5ToHex(password, 32);
    md5Password = md5Password.toLower();
    QString combined = md5Password + salt;
    QString encryptPassword = SecurityHelper::md5ToHex(combined, 32).toLower();

    return encryptPassword;
}

QString UserProxy::getPasswordSalt()
{
    QRandomGenerator generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    int randomInt = generator.bounded(1,10000);
    return QString::number(randomInt);
}
