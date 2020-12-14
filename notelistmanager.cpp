#include "notelistmanager.h"

NoteListManager::NoteListManager()
{

}
NoteListManager::NoteListManager(const NoteListManager& newNoteListManager){

    this->noteList=QList<note>(newNoteListManager.noteList);
}
bool NoteListManager::isTime(){
    if(this->noteList.isEmpty())
        return false;
    if(noteList.front().getDateTime()<=currentDateTimeObject.currentDateTime()) return true;
    return false;
}
void NoteListManager::push(const note & newNote){
    mutex.lock();
    if(!this->noteList.isEmpty())
    for(QList<note>::Iterator _begin=this->noteList.begin(), _end=this->noteList.end(); _begin!=_end; _begin++){
        if(_begin->getDateTime()>newNote.getDateTime()) {
            this->noteList.insert(_begin,newNote);
            mutex.unlock();
            return;
        }
    }
        this->noteList.push_back(newNote);
    mutex.unlock();
    //emit ListChaneged();
}
void NoteListManager::pop_front(){
    mutex.lock();
    if(noteList.isEmpty()) {
        mutex.unlock();
        return;
    }
    this->noteList.pop_front();
    mutex.unlock();
   // emit ListChaneged();
}
void NoteListManager::setNewNoteList(QList<note> &newNoteList){
    mutex.lock();
    noteList=newNoteList;
    mutex.unlock();
    //emit ListChaneged();
}
const QList<note>& NoteListManager::getNoteList() const{
       return noteList;
}
bool NoteListManager::isEmpty() const{
    if(noteList.isEmpty()) return true;
    return false;
}
const note& NoteListManager::front() const{
    return noteList.front();
}
void NoteListManager::push_front(const note &newNote){
    mutex.lock();
    noteList.push_front(newNote);
    mutex.unlock();
}
const QList<note>& NoteListManager::getNoteList(){
    return noteList;
}
void NoteListManager::setNote(const note& newNote){
    this->push(newNote);
}
void NoteListManager::removeOne(const note& oddNote){
    mutex.lock();
    if(!noteList.isEmpty()){
        noteList.removeOne(oddNote);
    }
    mutex.unlock();

}
void NoteListManager::NMSlot_remove_note(const note& oddNote){
    removeOne(oddNote);
}
QDataStream& operator <<(QDataStream &stream, NoteListManager* noteListManager)
{
    noteListManager->mutex.lock();
    if(!noteListManager->isEmpty())
    for(QList<note>::const_iterator _iter = noteListManager->noteList.begin(); _iter != noteListManager->noteList.end(); _iter++){
        stream << _iter->getData()<<_iter->getDateTime();
    }
    noteListManager->mutex.unlock();
return stream;
}
QDataStream& operator >>(QDataStream &stream, NoteListManager* noteListManager)
{
    noteListManager->mutex.lock();
    QString _temp_str;
    QDateTime _temp_date_time;
    while(!stream.atEnd()){
        stream >> _temp_str>>_temp_date_time;
        noteListManager->noteList.push_back(note(_temp_str,_temp_date_time));
    }
    noteListManager->mutex.unlock();
return stream;
}

