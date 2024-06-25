#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TSpinBoxDelegate;
class TDoubleSpinBoxDelegate;
class TComboBoxDelegate;

class QLabel;
class QStandardItemModel;
class QItemSelectionModel;
class QModelIndex;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    const int FixedColumnCount=6;
    QLabel *labCurFile;
    QLabel *labCellPos;
    QLabel *labCellText;

    TSpinBoxDelegate        *spinBoxDelegate;
    TDoubleSpinBoxDelegate  *D_spinBoxDelegate;
    TComboBoxDelegate       *comboBoxDelegate;

    QStandardItemModel *m_model;
    QItemSelectionModel *m_select;

    void iniModelData(QStringList &aFileContent);

private slots:
    void do_currentChanged(const QModelIndex &current,const QModelIndex &previous);

    void on_actAddTxt_triggered();

    void on_actPview_triggered();

    void on_actAddaRow_triggered();

    void on_actSortaRow_triggered();

    void on_actDelaRow_triggered();

    void on_actLeft_triggered();

    void on_actCenter_triggered();

    void on_actRight_triggered();

    void on_actBold_triggered(bool checked);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
