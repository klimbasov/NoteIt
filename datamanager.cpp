#include "datamanager.h"

DataManager::DataManager()
{}
void DataManager::loadTaskList(NoteListManager* noteListManager,const QString& filePath){
    QFile data(filePath);
    if(data.open(QIODevice::ReadOnly)){
    QDataStream stream;
    stream.setDevice(&data);
    stream.setVersion(QDataStream::Qt_5_9);
    stream >> noteListManager;
    }
    data.close();
}
void DataManager::saveTaskList( NoteListManager* noteListManager,const QString& filePath){
    QFile data(filePath);
    if(data.open(QIODevice::WriteOnly))
    {
    QDataStream stream;
    stream.setDevice(&data);
    stream.setVersion(QDataStream::Qt_5_9);
    stream << noteListManager;
    }
    //emit noteListSetted();
    data.close();
}


