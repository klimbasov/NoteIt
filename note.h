#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>
#include <QMetaType>
class note
{
    QDateTime noteDateTime;
    QString noteText;
public:

    explicit note();
    explicit note(const QString&, const QDateTime&);
    explicit note(const note&);

    void setData(const QString&);
    void setDateTime(const QDateTime&);
    const QString& getData() const;
    const QDateTime& getDateTime() const;
    bool operator == (const note&) const;
    bool operator != (const note&) const;

};
Q_DECLARE_METATYPE(note);

#endif // NOTE_H
