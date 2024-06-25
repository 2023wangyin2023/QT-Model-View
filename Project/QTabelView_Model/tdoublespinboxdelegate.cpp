#include "tdoublespinboxdelegate.h"
#include <QDoubleSpinBox>

TDoubleSpinBoxDelegate::TDoubleSpinBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

/**
 * @brief TDoubleSpinBoxDelegate::createEditor 创建QDoubleSpinBox代理编辑器
 * @param parent 对象树的父对象
 * @param option
 * @param index
 * @return 代理编辑器对象指针
 */
QWidget *TDoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);     // 设置无边框
    editor->setMinimum(0.00);
    editor->setMaximum(999999.99);
    return editor;
}

/**
 * @brief TDoubleSpinBoxDelegate::setEditorData
 * @param editor 编辑器对象
 * @param index 模型索引
 */
void TDoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox *>(editor);
    double value = index.model()->data(index,Qt::EditRole).toDouble();
    dSpinBox->setValue(value);
}

/**
 * @brief 将组件框内数据赋值给model模型
 * @param editor 编辑器对象
 * @param model 模型
 * @param index 模型索引
 */
void TDoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox *>(editor);
    double value = dSpinBox->value();
    model->setData(index,value,Qt::EditRole);
}

/**
 * @brief 设置组件框大小
 * @param editor 编辑对象
 * @param option 样式选项
 */
void TDoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);   // 根据给定的样式选项的范围属性设置
}
