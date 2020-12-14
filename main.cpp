#include "mainwindow.h"
#include "anotherwindow.h"
#include "note.h"
#include "notelistmanager.h"
#include "datamanager.h"
#include "widgettest.h"
#include "appclass.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppClass appClass(&a,a.applicationDirPath()+"/Data.bin");
    //appClass.CheckProsses();
//    a.quit();
    return a.exec();
}
