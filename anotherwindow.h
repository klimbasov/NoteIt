#ifndef ANOTHERWINDOW_H
#define ANOTHERWINDOW_H

#include <QWidget>
#include "note.h"
#include <QList>
#include <QApplication>

namespace Ui {
class anotherwindow;
}

class anotherwindow : public QWidget
{
    Q_OBJECT

public:
    explicit anotherwindow(QWidget *parent = nullptr);

    void redraw();
    ~anotherwindow();

public slots:
    void showNote(const note&);

private slots:
    void on_b_skip_clicked();
    void on_b_close_clicked();
    void on_b_next_clicked();
    void on_b_prev_clicked();

private:
    Ui::anotherwindow * ui;
    QList<note>       * listToShow;
    int                 counter=0;
};

#endif // ANOTHERWINDOW_H
