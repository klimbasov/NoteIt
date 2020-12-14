#ifndef NOTELISTMANAGER_H
#define NOTELISTMANAGER_H
#include "note.h"
#include <QList>
#include <QMutex>
#include <QDataStream>
class NoteListManager: public QObject
{
    Q_OBJECT
    QDateTime currentDateTimeObject;
    QList<note> noteList;
    QMutex mutex;
public:
    NoteListManager();
    NoteListManager(const NoteListManager&);
    bool isTime();
    void popFront();
    void push(const note&);
    void setNewNoteList(QList<note>&);
    const QList<note>& getNoteList() const;
    bool isEmpty() const;
    void pop_front();
    void push_front(const note&);
    const note& front() const;
    void removeOne(const note&);
    const QList<note>& getNoteList();
    friend QDataStream& operator <<(QDataStream &stream, NoteListManager*noteListManager);
    friend QDataStream& operator >>(QDataStream &stream, NoteListManager*noteListManager);

public slots:
    void setNote(const note&);
    void NMSlot_remove_note(const note&);
};
#endif // NOTELISTMANAGER_H

