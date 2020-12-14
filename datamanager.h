#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QDataStream>
#include "notelistmanager.h"
#include "note.h"
#include <QObject>

#define PATH ":/binaryDATA/DATA.bin"

class DataManager:public QObject
{
    Q_OBJECT
public:
    DataManager();
    void loadTaskList(NoteListManager* ,const QString& =QString(PATH));
    void saveTaskList( NoteListManager*, const QString& =QString(PATH));

signals:
   // void noteListSetted();
};

#endif // DATAMANAGER_H
