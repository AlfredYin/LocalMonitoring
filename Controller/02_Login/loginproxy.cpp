#include "loginproxy.h"
#include "loginresult.h"
#include "loginparam.h"

#include "mysqldbmanager.h"

#include "securityhelper.h"

// 初始化名称
LoginProxy::LoginProxy()
{
    PROXY_NAME = "LoginProxy";
}

// 处理真正的业务逻辑和数据操作。可以作为数据模型的抽象层，与数据库或其他数据源交互。
void LoginProxy::checkLogin(LoginParam *loginParam)
{
    LoginResult *loginResult = new LoginResult();

    QString name = loginParam->name;
    QString passwd = loginParam->password;

    qDebug()<<"name:" << name << ", passwd:" << passwd;

    QString queryStr="SELECT id,UserName, Password, Salt FROM SysUser";
    QSqlQuery query=executeQuery(queryStr);

    // if (user.Password == EncryptUserPassword(password, user.Salt))

    loginResult->result = false;
    while (query.next()) {
        float id = query.value(0).toFloat();

        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        QString salt = query.value(3).toString();
        qDebug() << "id:" << id << "username:" << username << ", Password:" << password << "salt:" << salt;

        if(name==username){
            if(password==EncryptUserPassword(passwd,salt)){
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

    QString queryStr="SELECT id,UserName, Password, Salt FROM SysUser";
    QSqlQuery query=executeQuery(queryStr);

    loginResult->result = true;
    while (query.next()) {

        float id = query.value(0).toFloat();

        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        QString salt = query.value(3).toString();
        qDebug() << "id:" << id << "username:" << username << ", Password:" << password << "salt:" << salt;

        if(name==username){
            if(password==EncryptUserPassword(passwd,salt)){
                loginResult->result = false;
                loginResult->message = "新密码与老密码相同";
                break;
            }
        }
    }


    // 随机生产密码盐 根据修改的密码重新生产
    if(loginResult->result){
        query.prepare("UPDATE `AlfredDb`.`SysUser` SET Password=:passwd,Salt=:salt WHERE UserName=:user;");
        query.bindValue(":user",name);
        query.bindValue(":passwd",passwd);
        query.bindValue(":salt",salt);

        if(query.exec()){
            loginResult->result = true;
        }
    }
    sendNotification("change_passwd_finished", (void *)loginResult);
}

QString LoginProxy::EncryptUserPassword(QString password, QString salt)
{

    QString md5Password = SecurityHelper::md5ToHex(password, 32);
    md5Password = md5Password.toLower();
    QString combined = md5Password + salt;
    QString encryptPassword = SecurityHelper::md5ToHex(combined, 32).toLower();

    qDebug()<<encryptPassword;

    return encryptPassword;
}

//private string EncryptUserPassword(string password, string salt)
//{
//    string md5Password = SecurityHelper.MD5ToHex(password);
//    string encryptPassword = SecurityHelper.MD5ToHex(md5Password.ToLower() + salt).ToLower();
//    return encryptPassword;
//}
