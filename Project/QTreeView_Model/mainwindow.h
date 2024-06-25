#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QFileSystemModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QFileSystemModel    *m_model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actRoot_triggered();

    void on_radioShowALL_clicked(bool checked);

    void on_radioShowDirOnly_clicked(bool checked);

    void on_comboBoxFile_currentTextChanged(const QString &arg1);

    void on_chkBoxFilter_clicked(bool checked);

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
