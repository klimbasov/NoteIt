#include "note.h"

note::note()
{
    qRegisterMetaType<note>("note");
}
note::note(const QString& HTML_TEXT, const QDateTime& SETTED_TIME)
{
    qRegisterMetaType<note>("note");
    noteText =  HTML_TEXT;
    noteDateTime = SETTED_TIME;
}
note::note(const note& COPY_NOTE){
    qRegisterMetaType<note>("note");
    noteText = COPY_NOTE.getData();
    noteDateTime = COPY_NOTE.getDateTime();
}
void note::setData(const QString& HTML_TEXT){
    this->noteText=  HTML_TEXT;
}
const QString& note::getData() const{
    return noteText;
}
void note::setDateTime(const QDateTime & dataTimeValue){
    noteDateTime = dataTimeValue;
}
const QDateTime& note::getDateTime() const{
    return noteDateTime;
}
bool note::operator==(const note & toCompare) const{
    if(this->getDateTime()==toCompare.getDateTime()&&  this->getData()==toCompare.getData()) return true;
    return false;
}

