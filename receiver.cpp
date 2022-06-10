#include <QUdpSocket>
#include "receiver.h"

Receiver::Receiver(Widget *w, QObject *parent)
    : QObject{parent}, m_widget(w)
{
    udpSocket = new QUdpSocket(this);
        udpSocket->bind(PORT_NBR, QUdpSocket::ShareAddress);

        connect(udpSocket, &QUdpSocket::readyRead,
                this, &Receiver::processPendingDatagrams);

        connect(this, &Receiver::datagramRecd, m_widget, &Widget::processMsg);
}
void Receiver::processPendingDatagrams()
{
    QByteArray datagram;

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        emit datagramRecd(datagram.data());
    }

}
