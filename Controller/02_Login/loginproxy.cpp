#include "loginproxy.h"
#include "loginresult.h"
#include "loginparam.h"

#include "mysqldbmanager.h"

// 初始化名称
LoginProxy::LoginProxy()
{
    PROXY_NAME = "LoginProxy";
}

// 处理真正的业务逻辑和数据操作。可以作为数据模型的抽象层，与数据库或其他数据源交互。
void LoginProxy::checkLogin(LoginParam *loginInfo)
{
    LoginResult *loginResult = new LoginResult();

    QString name = loginInfo->name;
    QString passwd = loginInfo->password;

    qDebug()<<"name:" << name << ", passwd:" << passwd;

    QString queryStr="SELECT id, username, password FROM users";
    QSqlQuery query=executeQuery(queryStr);

    loginResult->result = false;
    while (query.next()) {
        int id = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        qDebug() << "id:" << id << "username:" << username << ", Password:" << password;
        if(name==username){
            if(passwd==password){
                loginResult->result = true;
                loginResult->username=username;
                loginResult->passwd=passwd;
                break;
            }
        }
    }

    // 发送成功的通知
    sendNotification("login_finished", (void *)loginResult);
}

void LoginProxy::changePwd(LoginParam *loginInfo)
{
    LoginResult *loginResult = new LoginResult();

    QString name = loginInfo->name;
    QString passwd = loginInfo->password;

    qDebug()<<"name:" << name << ", passwdChange:" << passwd;

    QSqlQuery query(MySqlDBManager::instance().getDatabase());
    query.exec("SELECT id, username, password FROM users");

    loginResult->result = true;
    while (query.next()) {
        int id = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        qDebug() << "id:" << id << "username:" << username << ", Password:" << password;
        if(name==username){
            if(passwd==password){
                loginResult->result = false;
                loginResult->message = "新密码与老密码相同";
                break;
            }
        }
    }

    if(loginResult->result){
        query.prepare("UPDATE `AlfredDb`.`users` SET password=:passwd WHERE username=:user;");
        query.bindValue(":user",name);
        query.bindValue(":passwd",passwd);

        if(query.exec()){
            loginResult->result = true;
        }
    }
    sendNotification("change_passwd_finished", (void *)loginResult);
}
