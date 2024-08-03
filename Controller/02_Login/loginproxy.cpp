#include "loginproxy.h"

#include "loginresult.h"
#include "changepwdresult.h"
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

    QString queryStr="SELECT id,UserName,RealName,Password, Salt FROM SysUser Where UserName=:username";
    QSqlQuery query=executeQuery(queryStr,{{":username",name}});

    // if (user.Password == EncryptUserPassword(password, user.Salt))

    loginResult->result = false;

    if(query.first()){
        float id = query.value(0).toFloat();

        QString username = query.value(1).toString();
        QString realname = query.value(2).toString();
        QString password = query.value(3).toString();
        QString salt = query.value(4).toString();

        if(name==username){
            if(password==EncryptUserPassword(passwd,salt)){
                loginResult->result = true;
                loginResult->username=username;
                loginResult->realname=realname;
                loginResult->passwd=passwd;
            }
        }
    }else{
        loginResult->result = false;
    }

    // 发送成功的通知
    sendNotification("login_finished", (void *)loginResult);
}

void LoginProxy::changePwd(LoginParam *loginInfo)
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

QString LoginProxy::EncryptUserPassword(QString password, QString salt)
{

    QString md5Password = SecurityHelper::md5ToHex(password, 32);
    md5Password = md5Password.toLower();
    QString combined = md5Password + salt;
    QString encryptPassword = SecurityHelper::md5ToHex(combined, 32).toLower();

    return encryptPassword;
}

QString LoginProxy::getPasswordSalt()
{
    QRandomGenerator generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    int randomInt = generator.bounded(1,10000);
    return QString::number(randomInt);
}
