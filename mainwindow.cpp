#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QLabel>
#include <QSettings>


MainWindow::MainWindow(bool isClicked, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    noteList = new QList<note>;
    ui->setupUi(this);
    if(isClicked)
    ui->checkBox->setCheckState(Qt::CheckState::Checked);
    else
    ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(this, SIGNAL(MWSignal_Table_fill()), this, SLOT(MWSlot_Fill_Table()));

        trayIcon = new QSystemTrayIcon(this);
        //trayIcon->setIcon(QIcon(":/other/icon.ico"));
        trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
        trayIcon->setToolTip("NoteIt");

        QMenu * menu = new QMenu(this);

        QAction * viewWindow = new QAction(trUtf8("open"), this);
        QAction * quitAction = new QAction(trUtf8("close"), this);


        connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
        connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
        menu->addAction(viewWindow);
        menu->addAction(quitAction);

        trayIcon->setContextMenu(menu);
        trayIcon->show();

        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}



MainWindow::~MainWindow()
{
    delete ui;
    delete noteList;
    delete trayIcon;
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(this->isVisible()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        trayIcon->showMessage("NoteIt",
                              trUtf8("App is in a tray."),
                              icon,
                              2000);
    }
    else {
        emit MWSignal_Finish_Execution();
        event->accept();
    }
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:

            if(!this->isVisible()){
                this->show();
            } else {
                this->hide();
            }

        break;
    default:
        break;
    }
}

void MainWindow::MWSlot_Fill_Table(){
    if(noteList){
    int counter = 0;
    ui->tableWidget->setRowCount(noteList->size());
    if(!noteList->isEmpty())
    for(QList<note>::iterator _begin=this->noteList->begin(),_end=this->noteList->end(); _begin!=_end; _begin++){
        QLabel* label = new QLabel();
        label->setText(_begin->getData());
        QTableWidgetItem *dateTimeItem = new QTableWidgetItem(_begin->getDateTime().toString());
        ui->tableWidget->setCellWidget(counter,0,label);
     ui->tableWidget->setItem(counter,1,dateTimeItem);
     ++counter;
     label=nullptr;
    }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->stackedWidget->currentIndex()==0)
    ui->stackedWidget->setCurrentIndex(1);
    else
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_pushButton_save_and_exit_clicked()
{
    emit MWSignal_Note_Setted(note(ui->textEdit->toHtml(), ui->dateTimeEdit->dateTime()));
    emit MWSignal_NoteList_Copy_Needed();
    emit MWSignal_Table_fill();
    ui->textEdit->clear();
    this->close();
}

void MainWindow::on_pushButton_save_clicked()
{
    emit MWSignal_Note_Setted(note(ui->textEdit->toHtml(), ui->dateTimeEdit->dateTime()));
    emit MWSignal_NoteList_Copy_Needed();
    emit MWSignal_Table_fill();
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_close_clicked()
{
    ui->textEdit->clear();
    this->close();
}
void MainWindow::MWSlot_Finish_Execution(){
    emit MWSignal_Finish_Execution();
}
void MainWindow::MWSlot_NoteList_Set(const QList<note>& newNoteList){
    if(this->noteList)
        delete  this->noteList;
    this->noteList = new QList<note>(newNoteList);
    emit MWSignal_Table_fill();
}
void MainWindow::listenToNoteListStratSetting(){
    emit this->MWSignal_NoteList_Copy_Needed();
    emit this->MWSignal_Table_fill();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(!ui->tableWidget->selectionModel()->hasSelection())
        return;

    emit MWSignal_delete_Note(note(noteList->at(ui->tableWidget->selectionModel()->currentIndex().row())));
    ui->textEdit->setText(noteList->at(ui->tableWidget->selectionModel()->currentIndex().row()).getData());
    ui->dateTimeEdit->setDateTime(noteList->at(ui->tableWidget->selectionModel()->currentIndex().row()).getDateTime());
    on_pushButton_4_clicked();
    listenToNoteListStratSetting();
}

void MainWindow::on_pushButton_6_clicked()
{
    if(!ui->tableWidget->selectionModel()->hasSelection())
        return;

    emit MWSignal_delete_Note(note(noteList->at(ui->tableWidget->selectionModel()->currentIndex().row())));
    listenToNoteListStratSetting();
}

void MainWindow::on_checkBox_clicked()
{
 emit MWSignal_Startup_setting_send(ui->checkBox->isChecked());
}
