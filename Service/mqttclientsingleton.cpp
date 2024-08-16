#include "mqttclientsingleton.h"

// 在源文件中定义静态成员变量
QScopedPointer<QMQTT::Client> MqttClientSingleton::_instance;
QMutex MqttClientSingleton::mutex; // 定义静态互斥量

QMQTT::Client *MqttClientSingleton::instance()
{
    if (!_instance) {   // 如果 _instance 已经存在（即已经创建了单例实例），则不需要创建新的实例。
                       // 这个检查是为了避免在多线程环境中重复创建实例。
       // QMutexLocker 是一个RAII类，它在构造时自动锁定传入的 QMutex，在析构时自动解锁。
       // 这保证了在 _instance 初始化期间，其他线程无法进入临界区，防止竞态条件。
       QMutexLocker locker(&mutex);
       // 这是一个嵌套的条件检查，确保即使在 QMutexLocker 锁定的情况下，仍然只有一个线程能创建 _instance。
       // 这是双重检查锁定模式（Double-Check Locking）的实现方式，用于提高性能。
       if (!_instance) {
           // 证书部分
           QByteArray ba_crt,ba_crt_client,ba_crt_client_key;
           QFile ca_crtf(":/ssl/cert/server.crt"),ca_crtf_client(":/ssl/cert/client.crt"),ca_crtf_client_key(":/ssl/cert/client.key");
           if(ca_crtf.open(QIODevice::ReadOnly)&&ca_crtf_client.open(QIODevice::ReadOnly)&&ca_crtf_client_key.open(QIODevice::ReadOnly)){
               ba_crt = ca_crtf.readAll();ca_crtf.close();
               ba_crt_client = ca_crtf_client.readAll();ca_crtf_client.close();
               ba_crt_client_key = ca_crtf_client_key.readAll();ca_crtf_client_key.close();
           }else{
               qDebug()<<"Error Certificate Read File";
               return _instance.data();
           }
           // Ssl 配置部分
           QSslConfiguration config;
           QSslCertificate ca_crt(ba_crt, QSsl::Pem);
           QSslCertificate ca_crt_client(ba_crt_client,QSsl::Pem);
           QSslKey ca_crt_client_key(ba_crt_client_key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
           config.defaultConfiguration();
           config.setProtocol(QSsl::TlsV1_2);
           config.setCaCertificates({ca_crt});
           config.setPeerVerifyMode(QSslSocket::AutoVerifyPeer);
           config.setLocalCertificate(ca_crt_client);
           config.setPrivateKey(ca_crt_client_key);

           // reset 方法会先释放旧的实例（如果有的话），然后设置新的实例。
           _instance.reset(new QMQTT::Client("47.98.243.38", 1884, config));
           _instance->setClientId("QT");
           _instance->setCleanSession(true);       // 保留/不保留（false/true）会话状态
       }
    }
    // 返回 _instance 的原始指针。_instance 是一个 QScopedPointer，它的 data() 方法返回指向 QMQTT::Client 实例的原始指针。
    // QScopedPointer 用于自动管理内存，确保对象在不再需要时被正确释放。
    return _instance.data();
}
