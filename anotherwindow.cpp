#include "anotherwindow.h"
#include "ui_anotherwindow.h"
#include <QDesktopWidget>


anotherwindow::anotherwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::anotherwindow)
{
    QDesktopWidget desktopWidget;
    this->setGeometry(4.5*desktopWidget.width()/7,0,desktopWidget.width()/7,desktopWidget.height()/7);
    ui->setupUi(this);
    listToShow = new QList<note>;
    this->setWindowFlags(Qt::WindowTitleHint|Qt::FramelessWindowHint);
}

void anotherwindow::redraw(){
    ui->L_note->setText(listToShow->at(counter).getData());
    ui->L_timeDate->setText(listToShow->at(counter).getDateTime().toString());
}

anotherwindow::~anotherwindow()
{
    delete listToShow;
    delete ui;
}

void anotherwindow::showNote(const note & currentNote){
    if(listToShow->isEmpty()){
        listToShow->push_back(currentNote);
        this->redraw();
        this->show();
    }
    else{
        listToShow->push_back(currentNote);
        if(this->isHidden())
            this->show();
    }
}


void anotherwindow::on_b_skip_clicked()
{
    if(listToShow->size()==1){
        on_b_close_clicked();
        return;
    }
    if(listToShow->size()==counter-1){
        listToShow->removeAt(counter);
        --counter;
    }
    else{
        listToShow->removeAt(counter);
        ++counter;
    }
    redraw();
}
void anotherwindow::on_b_close_clicked()
{
    this->hide();
    listToShow->clear();
}

void anotherwindow::on_b_next_clicked()
{
    if(counter<listToShow->size()-1){
    ++counter;
    redraw();
    }
}

void anotherwindow::on_b_prev_clicked()
{
    if(counter>0){
    --counter;
    redraw();
    }
}
