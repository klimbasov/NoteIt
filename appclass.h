#ifndef APPCLASS_H
#define APPCLASS_H

#include "mainwindow.h"
#include "anotherwindow.h"
#include "datamanager.h"
#include "notelistmanager.h"
#include <QApplication>
#include <QTimer>

class AppClass:public QObject
{
Q_OBJECT
public:
    AppClass(QApplication*, const QString path = ":/binaryDATA/DATA.bin" );
    //void CheckProsses();
    ~AppClass();
signals:
    void APSignal_Show_Request(const note&);
    void APSignal_Finish_Execution();

    void APSignal_Copy_Export(const QList<note>&);
public slots:
    void APSlot_sturtup_setting_change(bool);
    void APSlot_Copy_Request();
    void APSlot_Finish_Execution ();
    void APSlot_Check_notes();
private:
    QApplication* current_app;
    DataManager* dataMeneger;
    NoteListManager* noteListManager;
    MainWindow* mainWindow;
    anotherwindow* anotherWindow;
    QString path;
    QTimer* timer;

};


#endif // APPCLASS_H
