#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "ipinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void processMsg(QByteArray msg);

private slots:
    void on_pushButtonCopySerial_clicked();

    void on_pushButtonCopyMac_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::Widget *ui;
    IpInfo m_ipInfo;
    void populateInfoField();
};
#endif // WIDGET_H
