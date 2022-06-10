#include "ipinfo.h"

IpInfo::IpInfo(QObject *parent)
    : QObject{parent}
{
}
void IpInfo::initHostTable()
{
    QList<QNetworkInterface> nics; // list of "usable" NICs on host.
    QList<QNetworkInterface>::iterator nic;
    QList<QNetworkAddressEntry> addrs; // list of addresses on a NIC.
    QList<QNetworkAddressEntry>::iterator addr;
    QNetworkInterface::InterfaceFlags flags;
    QNetworkInterface::InterfaceType type;
    QHostAddress qha;
    QString nicName;
    NicInfo nicInfo;

    // get a list of all the interfaces on the host system.
    nics = QNetworkInterface::allInterfaces();

    // iterate through the interfaces.
    for (nic = nics.begin(); nic != nics.end(); ++nic)
    {
        // skip over any of the interfaces we can't use.
        flags = nic->flags();
        type = nic->type();
        nicName = nic->humanReadableName();
        if (nicName.contains("Loopback"))
        {
            continue;
        }
        if (nicName.contains("Bluetooth"))
        {
            continue;
        }
        if (nicName.contains("Virtual"))
        {
            continue;
        }
        if ((type != QNetworkInterface::Ethernet) &&
            (type != QNetworkInterface::Wifi))
        {
            continue;
        }
        if (!(flags & QNetworkInterface::IsUp))
        {
            continue;
        }
        if  (!(flags & QNetworkInterface::IsRunning))
        {
            continue;
        }
        if (flags & QNetworkInterface::IsLoopBack)
        {
            continue;
        }
        if (!(flags & QNetworkInterface::CanMulticast))
        {
            continue;
        }

        // if we've gotten this far, we've found aninterface we want to display.
        // find the entry for the IPv4 address and add it to our list.
        addrs = nic->addressEntries();

        // for each address entry
        for (addr = addrs.begin(); addr != addrs.end(); ++addr)
        {
            qha = addr->ip();
            if (qha.protocol() == QAbstractSocket::IPv4Protocol) // currently ignoring IP6 addresses.
            {
                nicInfo.nic = *nic;
                nicInfo.addr = addr->ip().toString();
                nicInfo.name = nicName;
                m_socks.append(nicInfo);
                break;
            }
        }
    }
    return;
}
QVector<QString> IpInfo::getNicInfo()
{
    QVector<NicInfo>::iterator it;
    QString qs;
    QVector<QString> qsv;

    for (it = m_socks.begin(); it != m_socks.end(); it++) {
        qs = "IP Address " + it->addr + " (" + it->name + ")";
        qsv.append(qs);
    }
    return qsv;
}
