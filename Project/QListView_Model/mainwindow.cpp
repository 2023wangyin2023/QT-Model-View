#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_list<<"成龙"<<"李小龙"<<"龙在天"<<"龙傲天"<<"龙";
    m_model = new QStringListModel(this);
    m_model->setStringList(m_list);
    ui->listView->setModel(m_model);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|
                                  QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_viewBtnRecover_clicked()
{
    m_model->setStringList(m_list);
}


void MainWindow::on_viewBtnClear_clicked()
{
    m_model->removeRows(0, m_model->rowCount());
}


void MainWindow::on_chkBoxEdit_clicked(bool checked)
{
    if(checked)
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|
                                      QAbstractItemView::SelectedClicked);
    else
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_viewBtnAdd_clicked()
{
    m_model->insertRow(m_model->rowCount());
    QModelIndex index = m_model->index(m_model->rowCount()-1);
    m_model->setData(index,"new",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_viewBtnInsert_clicked()
{
    QModelIndex index_current = ui->listView->currentIndex();
    m_model->insertRow(index_current.row());
    m_model->setData(index_current,"new",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index_current);
}


void MainWindow::on_viewBtnDel_clicked()
{
    QModelIndex index_current = ui->listView->currentIndex();
    m_model->removeRow(index_current.row());
}

void MainWindow::on_viewBtnUp_clicked()
{
    QModelIndex index;
    int row = ui->listView->currentIndex().row();
    m_model->moveRow(index,row,index,row-1);
}


void MainWindow::on_viewBtnDown_clicked()
{
    QModelIndex index;
    int row = ui->listView->currentIndex().row();
    m_model->moveRow(index,row,index,row+2);
}


void MainWindow::on_viewBtnSort_clicked()
{
    m_model->sort(0,Qt::AscendingOrder);
}


void MainWindow::on_textBtnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_textBtnDisplay_clicked()
{
    ui->plainTextEdit->clear();
    QStringList list= m_model->stringList();
    for(int i=0;i<list.size();++i)
        ui->plainTextEdit->appendPlainText(list.at(i));
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString str = QString::asprintf("模型索引: row=%d, column=%d",index.row(),index.column());
    str+=m_model->data(index,Qt::DisplayRole).toString();
    ui->statusbar->showMessage(str);
}

