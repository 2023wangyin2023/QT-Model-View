#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFileDialog>

#include "tspinboxdelegate.h"
#include "tdoublespinboxdelegate.h"
#include "tcomboboxdelegate.h"

/******* 自定义槽函数 *********/

void MainWindow::iniModelData(QStringList &aFileContent)
{
    int rowSum = aFileContent.size();

    // 第一行赋值
    m_model->setRowCount(rowSum-1); // 第一行是标题
    QString header = aFileContent.at(0);  // 取出第一行
    // 按照给定的正则表达式进行分割 "\\s+" \\代表后面为特殊符 s+代表一或多空格space+
    // "\\s+" 也可以写为 R"(\s+)"
    QStringList headerlist = header.split(QRegularExpression(R"(\s+)"),Qt::SkipEmptyParts);
    m_model->setHorizontalHeaderLabels(headerlist);

    QStandardItem *item;
    for(int i=1;i<rowSum;i++){
        QString aLineText = aFileContent.at(i);
        QStringList tmplist = aLineText.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
        int j=0;
        for(;j<FixedColumnCount-1;j++){
            item=new QStandardItem(tmplist.at(j));
            m_model->setItem(i-1,j,item);
        }
        // 最后一列用复选框的形式
        item=new QStandardItem("");
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));
        if(tmplist.at(j)=="0")
            item->setCheckState(Qt::Unchecked);
        else
            item->setCheckState(Qt::Checked);
        m_model->setItem(i-1,j,item);
    }
}

// 当前底部状态更新
void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.isValid()){
        labCellPos->setText(QString::asprintf("当前单元格: %d行,%d列",current.row(),current.column()));
        QStandardItem *Item = m_model->itemFromIndex(current);
        labCellText->setText("单元格内容: "+Item->text());
        ui->actBold->setChecked(Item->font().bold());
    }
}


/********* 启动窗口 **********/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 滚动条显示
    labCurFile = new QLabel("当前文件",this);
    labCurFile->setMinimumWidth(200);
    labCellPos = new QLabel("当前单元格",this);
    labCellPos->setMinimumWidth(200);
    labCellText= new QLabel("单元格内容",this);
    labCellText->setMinimumWidth(200);
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);

    m_model = new QStandardItemModel(2,FixedColumnCount,this);
    m_select = new QItemSelectionModel(m_model);
    ui->tableView->setModel(m_model);           // 将 m_model 设置为 QTableView 的数据模型
    ui->tableView->setSelectionModel(m_select); // 将 m_select 设置为 QTableView 的选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);  //允许通过 Shift 键或 Ctrl 键进行扩展选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    // 设置视图的选择行为

    connect(m_select,&QItemSelectionModel::currentChanged,
            this,&MainWindow::do_currentChanged);

    spinBoxDelegate = new TSpinBoxDelegate(this);
    D_spinBoxDelegate = new TDoubleSpinBoxDelegate(this);
    comboBoxDelegate = new TComboBoxDelegate(this);
    QStringList list;
    list<<"强"<<"中"<<"弱";
    comboBoxDelegate->setItems(list,false);

    ui->tableView->setItemDelegateForColumn(1,spinBoxDelegate);// 第2列设置数值框代理
    ui->tableView->setItemDelegateForColumn(3,comboBoxDelegate);// 第4列设置下拉框代理
    ui->tableView->setItemDelegateForColumn(4,D_spinBoxDelegate);// 第5列设置double数值框代理

}

MainWindow::~MainWindow()
{
    delete ui;
}


/********* ui事件设置槽函数 *********/

void MainWindow::on_actAddTxt_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this,"选择文件",curPath,"数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isNull())
        return;

    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::ReadOnly|QIODevice::Text))    // 以只读/文本模式打开
        return;

    QStringList aFileContent;
    ui->plainTextEdit->clear();
    QTextStream aStream(&aFile);
    while(!aStream.atEnd()){
        QString str = aStream.readLine();
        ui->plainTextEdit->appendPlainText(str);
        aFileContent.append(str);
    }
    aFile.close();

    labCurFile->setText("当前文件: "+aFileName);
    ui->actAddaRow->setEnabled(true);
    ui->actSortaRow->setEnabled(true);
    ui->actDelaRow->setEnabled(true);
    ui->actPview->setEnabled(true);

    iniModelData(aFileContent);
}


void MainWindow::on_actPview_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem *item;
    QString str;
    for(int i=0;i<m_model->columnCount();++i){
        item = m_model->horizontalHeaderItem(i);
        str+=item->text();
        str+="\t";
    }

    ui->plainTextEdit->appendPlainText(str);

    for(int i=0;i<m_model->rowCount();++i){
        str = "";
        int j=0;
        for(;j<m_model->columnCount()-1;++j){
            item = m_model->item(i,j);
            str+=item->text();
            str+="\t";
        }

        item = m_model->item(i,j);
        if(item->checkState()==Qt::Checked)
            str+="是";
        else
            str+="否";

        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actAddaRow_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem * item;
    for(int i=0;i<m_model->columnCount()-1;++i){
        item = new QStandardItem("text");
        itemList<<item;
    }
    item = new QStandardItem();
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    itemList<<item;
    m_model->insertRow(m_model->rowCount(),itemList);
    m_select->clearSelection();
    m_select->setCurrentIndex(m_model->index(m_model->rowCount()-1,0),
                              QItemSelectionModel::Select);
}


void MainWindow::on_actSortaRow_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem * item;
    for(int i=0;i<m_model->columnCount()-1;i++){
        item = new QStandardItem("text");
        itemList<<item;
    }
    item = new QStandardItem();
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    itemList<<item;
    QModelIndex curIndex = m_select->currentIndex();
    m_model->insertRow(curIndex.row()+1,itemList);
    m_select->clearSelection();
    m_select->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}


void MainWindow::on_actDelaRow_triggered()
{
    QModelIndex curIndex = m_select->currentIndex();
    int curRow = curIndex.row();

    if(curRow>=0 && curRow<m_model->rowCount()){
        m_model->removeRow(curIndex.row());     // 移除后m_model->rowCount()会少一
        m_select->clearSelection();

        // 去判断下一选择索引应该在哪
        int nextRow = curRow<m_model->rowCount()? curRow : curRow-1;
        if(nextRow>=0){
            QModelIndex nextIndex = m_model->index(nextRow,curIndex.column());
            m_select->setCurrentIndex(nextIndex,QItemSelectionModel::Select);
        }
    }
}


void MainWindow::on_actLeft_triggered()
{
    if(!m_select->hasSelection())
        return;

    QModelIndexList indexList = m_select->selectedIndexes();
    for(auto index:indexList){
        m_model->itemFromIndex(index)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }
}


void MainWindow::on_actCenter_triggered()
{
    if(!m_select->hasSelection())
        return;

    QModelIndexList indexList = m_select->selectedIndexes();
    for(auto index:indexList){
        m_model->itemFromIndex(index)->setTextAlignment(Qt::AlignCenter);
    }
}


void MainWindow::on_actRight_triggered()
{
    if(!m_select->hasSelection())
        return;

    QModelIndexList indexList = m_select->selectedIndexes();
    for(auto index:indexList){
        m_model->itemFromIndex(index)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
}

void MainWindow::on_actBold_triggered(bool checked)
{
    if(!m_select->hasSelection())
        return;

    QModelIndexList indexList = m_select->selectedIndexes();
    for(auto index:indexList){
        QFont font = m_model->itemFromIndex(index)->font();
        font.setBold(checked);
        m_model->itemFromIndex(index)->setFont(font);
    }
}

