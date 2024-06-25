#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class QStringListModel;     // 定义了指针若不包含头文件 需要声明类

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_viewBtnRecover_clicked();

    void on_viewBtnClear_clicked();

    void on_chkBoxEdit_clicked(bool checked);

    void on_viewBtnAdd_clicked();

    void on_viewBtnInsert_clicked();

    void on_viewBtnDel_clicked();

    void on_viewBtnUp_clicked();

    void on_viewBtnDown_clicked();

    void on_viewBtnSort_clicked();

    void on_textBtnClear_clicked();

    void on_textBtnDisplay_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    QStringList m_list;
    QStringListModel *m_model;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
