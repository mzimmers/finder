#ifndef IPINFO_H
#define IPINFO_H

#include <QObject>
#include <QHostAddress>
#include <QVector>
#include <QNetworkDatagram>
#include <QNetworkInterface>

struct NicInfo
{
    QNetworkInterface nic;
    QString addr;
    QString name;
};

typedef QVector<QString> nics;

class IpInfo : public QObject
{
    Q_OBJECT
private:
    QVector<NicInfo> m_socks;
public:
    explicit IpInfo(QObject *parent = nullptr);
    void initHostTable();
    QVector<QString> getNicInfo();
signals:

};

#endif // IPINFO_H
