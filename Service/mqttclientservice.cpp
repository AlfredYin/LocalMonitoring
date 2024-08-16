#include "mqttclientservice.h"
#include <QIODevice>

MqttClientService::MqttClientService(QObject *parent) : QObject{parent}
{
    QByteArray ba_crt;
    QByteArray ba_crt_client;
    QByteArray ba_crt_client_key;

    QFile ca_crtf(":/ssl/cert/server.crt");
    QFile ca_crtf_client(":/ssl/cert/client.crt");
    QFile ca_crtf_client_key(":/ssl/cert/client.key");

    if (!ca_crtf.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Opening file: ca.crt";
    } else {
        ba_crt = ca_crtf.readAll();
        ca_crtf.close();
        qDebug() << "Read CA certificate";
    }
    if (!ca_crtf_client.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Opening file: ca.crt_client";
    } else {
        ba_crt_client = ca_crtf_client.readAll();
        ca_crtf_client.close();
        qDebug() << "Read CA Client certificate";
    }
    if (!ca_crtf_client_key.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Opening file: ca.crt_client_key";
    } else {
        ba_crt_client_key = ca_crtf_client_key.readAll();
        ca_crtf_client_key.close();
        qDebug() << "Read CA Client Key certificate";
    }

    QSslCertificate ca_crt(ba_crt, QSsl::Pem);

    QSslCertificate ca_crt_client(ba_crt_client,QSsl::Pem);
    QSslKey ca_crt_client_key(ba_crt_client_key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);

    config.defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    // 将 CA 证书设置到配置中
//    config.addCaCertificate(ca_crt);  Qt 版本低，没有这个功能
    config.setCaCertificates({ca_crt});

    config.setPeerVerifyMode(QSslSocket::AutoVerifyPeer);	// Dont check hostname from certificate
    // 双端验证添加
    config.setLocalCertificate(ca_crt_client);
    config.setPrivateKey(ca_crt_client_key);

//    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    // Add custom SSL options here (for example extra certificates)
    client = new QMQTT::Client("47.98.243.38", 1884, config);
    client->setClientId("QT");

    // Optionally, set ssl errors you want to ignore. Be careful, because this may weaken security.
    // See QSslSocket::ignoreSslErrors(const QList<QSslError> &) for more information.
//    client->ignoreSslErrors(<list of expected ssl errors>)
    client->connectToHost();

}

void MqttClientService::connectInit()
{

}

void MqttClientService::connectMqttServerSsl(QSslConfiguration config)
{

}
