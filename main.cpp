#include <QApplication>

#include "widget.h"
#include "receiver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Receiver *r;
    Q_UNUSED (r) // to suppress the compiler warning.

    r = new Receiver(&w);
    w.show();
    return a.exec();

    return 0;
}
