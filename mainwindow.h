#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notelistmanager.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool ,QWidget *parent = nullptr);
    ~MainWindow();
protected:

    void closeEvent(QCloseEvent * event);

public slots:
    void MWSlot_Finish_Execution();
    void MWSlot_NoteList_Set(const QList<note>&);
    void listenToNoteListStratSetting();
private slots:
    void MWSlot_Fill_Table();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_pushButton_4_clicked();

    void on_pushButton_save_and_exit_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_checkBox_clicked();

signals:
    void MWSignal_Finish_Execution();
    void MWSignal_Note_Setted(const note&);
    void MWSignal_NoteList_Copy_Needed();
    void MWSignal_Table_fill();
    void MWSignal_delete_Note(const note&);
    void MWSignal_Startup_setting_send(bool);
private:
    Ui::MainWindow          * ui;
    QList<note>             * noteList;
    QSystemTrayIcon         * trayIcon;
};

#endif // MAINWINDOW_H
