#include "appclass.h"
#include <QSettings>
#include <QDir>

AppClass::AppClass(QApplication* this_application, const QString path):path(path)
{
    timer = new QTimer();
    timer->setInterval(5000);
    current_app = this_application;
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if(settings.contains(current_app->applicationDisplayName()))
    mainWindow = new MainWindow(true);
    else
    mainWindow = new MainWindow(false);
    anotherWindow = new anotherwindow();
    dataMeneger = new DataManager();
    noteListManager = new NoteListManager();
    connect(timer, SIGNAL(timeout()), this, SLOT(APSlot_Check_notes()));
    connect(mainWindow, SIGNAL(MWSignal_Note_Setted(const note&)), noteListManager, SLOT(setNote(const note&)));
    connect(mainWindow, SIGNAL(MWSignal_Finish_Execution()), this, SLOT(APSlot_Finish_Execution()));
    connect(this_application, SIGNAL(aboutToQuit()), this, SLOT(APSlot_Finish_Execution()));
    connect(this, SIGNAL(APSignal_Show_Request(const note&)),anotherWindow,SLOT(showNote(const note&)));
    connect(mainWindow, SIGNAL(MWSignal_Startup_setting_send(bool)), this,SLOT(APSlot_sturtup_setting_change(bool)));
    connect(this, SIGNAL(APSignal_Copy_Export(const QList<note>&)), mainWindow, SLOT(MWSlot_NoteList_Set(const QList<note>&)));
    connect(mainWindow, SIGNAL(MWSignal_NoteList_Copy_Needed()), this, SLOT(APSlot_Copy_Request()));
    connect(dataMeneger, SIGNAL(noteListSetted()), mainWindow, SLOT(listenToNoteListStratSetting()));
    connect(mainWindow, SIGNAL(MWSignal_delete_Note(const note &)), noteListManager, SLOT(NMSlot_remove_note(const note&)));
    connect(this, SIGNAL(APSignal_Finish_Execution()), this_application, SLOT(closeAllWindows()));
    connect(this, SIGNAL(APSignal_Finish_Execution()), mainWindow, SLOT(close()));
    //connect(dataMeneger, SIGNAL(noteListSetted()), this, SLOT(APSlot_Copy_Request()));
    //connect(dataMeneger, SIGNAL(noteListSetted()), mainWindow, SLOT(MWSlot_Fill_Table()));
    dataMeneger->loadTaskList(noteListManager, path);
    delete dataMeneger;
    timer->start();
    mainWindow->show();
}
void AppClass::APSlot_Finish_Execution(){
    dataMeneger = new DataManager();
    dataMeneger->saveTaskList(noteListManager, path);
    delete dataMeneger;
}
void AppClass::APSlot_Copy_Request(){
    emit APSignal_Copy_Export(noteListManager->getNoteList());
}
void AppClass::APSlot_sturtup_setting_change(bool setting){
    if(setting){
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.setValue(current_app->applicationDisplayName(), QDir::toNativeSeparators(current_app->applicationFilePath()));
            settings.sync();
    }
    else{
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.remove(current_app->applicationDisplayName());
    }
}
void AppClass::APSlot_Check_notes(){
    if(!noteListManager->isEmpty())
          while(noteListManager->isTime()){
            emit APSignal_Show_Request(noteListManager->front());
            noteListManager->pop_front();
          }
}
AppClass::~AppClass(){
    delete mainWindow;
    delete anotherWindow;
    delete noteListManager;
}
