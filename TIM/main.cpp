#include "TIM.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TIM w;
    w.show();
    return a.exec();
}
