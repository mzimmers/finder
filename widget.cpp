#include <QClipboard>
#include <QDateTime>
#include <iomanip>

#include "macaddr_utils.h"
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);

    populateInfoField();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::populateInfoField() {
    QString qs;
    QVector<QString> qsv;
    QVector<QString>::Iterator it;

    // version information (hard-coded for now).
    ui->textEditStatus->append("Version 6.0.2");

    // get the "live" interface info.
    m_ipInfo.initHostTable();
    qsv = m_ipInfo.getNicInfo();
    for (it = qsv.begin(); it !=qsv.end(); it++) {
        qs = *it;
        ui->textEditStatus->append(qs);
    }

    // date and time.
    ui->textEditStatus->append(QDateTime::currentDateTime().toString());

}
void Widget::processMsg(QByteArray msg)
{
    QByteArray qba = msg;
    QString sn;
    std::string mac;
    int msgLen;
    QString msgLenStr;
    std::stringstream qts;
    std::string msgString;

    // byte 16 contains the 6-byte MAC address.
    qba = msg.right(6);
    mac_itos(mac, (uint8_t *) qba.constData());
    ui->textEditMac->setText("MAC: " + QString::fromStdString(mac));
    ui->textEditMac->setAlignment(Qt::AlignCenter);

    // byte 2 contains the 12-byte serial number.
    sn = msg.left(14);
    sn = sn.right(12);
    // insert "-" for readability.
    sn.insert(9, "-");
    sn.insert(6, "-");
    sn.insert(3, "-");
    ui->textEditSerial->setPlainText(sn);
    ui->textEditSerial->setAlignment(Qt::AlignCenter);

    // add hex representation of message to main text area.
    ui->textEditStatus->append(QDateTime::currentDateTime().toString());
    msgLen = msg.size();
    msgLenStr = QString::number(msgLen);
    ui->textEditStatus->append("New message length " + msgLenStr);

    //convert message to readable hex representation
    qts << std::hex;
    for(int i = 0; i < msgLen; ++i) {
        // the casting of msg[i] needs an explanation:
        // stringstreams don't do well with 8-bit values,
        // so we need to cast it to a uint32_t. But this will propogate
        // the sign bit through all 32 bits, so we get 8 characters.
        // to get around this, first cast the array element to a uint8_t.
        qts << std::setfill ('0') << std::setw(2) << std::hex << (uint32_t)(uint8_t)msg[i];
    }
    msgString.append(qts.str());
    ui->textEditStatus->append(QString::fromStdString(msgString));
}

void Widget::on_pushButtonCopySerial_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->textEditSerial->toPlainText());
}

void Widget::on_pushButtonCopyMac_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->textEditMac->toPlainText());
}

void Widget::on_pushButtonClear_clicked()
{
    ui->textEditMac->clear();
    ui->textEditSerial->clear();
}

