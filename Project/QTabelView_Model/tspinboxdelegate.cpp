#include "tspinboxdelegate.h"

#include <QSpinBox>

/**
 * @brief TSpinBoxDelegate构造函数:初始化基类QStyledItemDelegate
 */
TSpinBoxDelegate::TSpinBoxDelegate(QObject *parent):QStyledItemDelegate(parent)
{}


/**
 * @brief TSpinBoxDelegate::createEditor 基于parent创建用于编辑模型数据的QSpinBox组件
 * @param parent 对象树的父对象
 * @param option
 * @param index
 * @return 代理编辑器对象指针
 */
QWidget *TSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);       // 无边框
    editor->setMinimum(0);
    editor->setMaximum(65536);
    return editor;
}

/**
 * @brief TSpinBoxDelegate::setEditorData 将model模型数据编辑到组件框内
 * @param editor 编辑器对象
 * @param index 模型索引
 */
void TSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *spinBox = dynamic_cast<QSpinBox *>(editor);   // 进行类型检查的安全转换
    int value = index.model()->data(index,Qt::EditRole).toInt();
    spinBox->setValue(value);
}

/**
 * @brief 将组件框内数据赋值给model模型
 * @param model 模型
 * @param index 模型索引
 */
void TSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox = dynamic_cast<QSpinBox *>(editor);
    int value = spinBox->value();
    model->setData(index,value,Qt::EditRole);
}

/**
 * @brief 设置组件框大小
 * @param editor 编辑对象
 * @param option 样式选项
 */
void TSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
