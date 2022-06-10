#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include "widget.h"

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

const int PORT_NBR = 30303;

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(Widget *w, QObject *parent = nullptr);
private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket = nullptr;
    Widget *m_widget;

signals:
    void datagramRecd(QByteArray dg);
};

#endif // RECEIVER_H
