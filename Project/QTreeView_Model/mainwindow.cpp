#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileSystemModel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new QFileSystemModel(this);
    ui->treeView->setModel(m_model);
    ui->tableView->setModel(m_model);
    ui->listView->setModel(m_model);

    // ui->treeView->setRootIndex(m_model->index(QDir::currentPath())); // 设置当前根目录
    m_model->setRootPath("");   // 显示根目录,若没设置根目录，默认就为 < 我的电脑 >

    connect(ui->treeView,&QTreeView::clicked,ui->listView,&QListView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,ui->tableView,&QTableView::setRootIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actRoot_triggered()
{
    QString Dir = QFileDialog::getExistingDirectory(this,"选择目录",QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly);
    if(Dir.isNull())
        return;

    ui->treeView->setRootIndex(m_model->index(Dir));
    ui->listView->setRootIndex(m_model->index(Dir));
    ui->tableView->setRootIndex(m_model->index(Dir));
}

/**
 * @brief MainWindow::on_radioShowALL_clicked 正常显示
 * @param checked
 */
void MainWindow::on_radioShowALL_clicked(bool checked)
{
    if(checked) // 过滤器 - 包含目录、文件和驱动器|不包含 . 和 .. 目录
    {
        m_model->setFilter(QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot);
        ui->comboBoxFile->setEnabled(true);
        ui->chkBoxFilter->setEnabled(true);
    }
}

/**
 * @brief MainWindow::on_radioShowDirOnly_clicked 只显示目录
 * @param checked
 */
void MainWindow::on_radioShowDirOnly_clicked(bool checked)
{
    if(checked) // 过滤器 - 只包含目录
    {
        m_model->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
        ui->comboBoxFile->setEnabled(false);
        ui->chkBoxFilter->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_comboBoxFile_currentTextChanged 槽函数，下拉文本发送变化时触发
 * @param arg1 当前 下拉框 的文本内容
 */
void MainWindow::on_comboBoxFile_currentTextChanged(const QString &arg1)
{
    QStringList strList= arg1.split(";",Qt::SkipEmptyParts);
    m_model->setNameFilters(strList);
}


void MainWindow::on_chkBoxFilter_clicked(bool checked)
{
    // 启用或禁用名称过滤 - 如果为 true，则禁用名称过滤；如果为 false，则启用名称过滤
    m_model->setNameFilterDisables(!checked);
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->labFileName->setText("文件名："+m_model->fileName(index));
    ui->labFilePath->setText("路径名："+m_model->filePath(index));
    ui->labFileType->setText("节点类型："+m_model->type(index));
    ui->chkIsDir->setChecked(m_model->isDir(index));
    int sz = m_model->size(index);
    if(sz<1024){
        ui->labFileSize->setText("文件大小："+QString("%1 字节").arg(sz));
    }
    else{
        double ds = sz / 1024.0;
        if(ds<1024.0)
            ui->labFileSize->setText("文件大小："+QString("%1 KB").arg(ds,0,'f',3));
        else
            ui->labFileSize->setText("文件大小："+QString::asprintf("%2.f MB",ds/1024.0));
    }


}

