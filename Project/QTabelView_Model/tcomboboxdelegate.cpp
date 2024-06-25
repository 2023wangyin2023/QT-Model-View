#include "tcomboboxdelegate.h"
#include <QComboBox>

/**
 * @brief TComboBoxDelegate::setItems 设置下拉框节点
 * @param items
 * @param editable
 */
void TComboBoxDelegate::setItems(QStringList items, bool editable)
{
    m_itemList = items;
    m_editable = editable;
}

/**
 * @brief TComboBoxDelegate::TComboBoxDelegate 构造
 * @param parent 为初始基类对象
 */
TComboBoxDelegate::TComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

/**
 * @brief TComboBoxDelegate::createEditor 创建编辑器
 * @param parent 父对象
 * @param option 样式选项
 * @param index 索引
 * @return
 */
QWidget *TComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(m_editable);
    for(const auto &item:m_itemList)
        editor->addItem(item);

    return editor;
}

/**
 * @brief TComboBoxDelegate::setEditorData
 * @param editor
 * @param index
 */
void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox *>(editor);
    QString str = index.model()->data(index,Qt::EditRole).toString();
    comboBox->setCurrentText(str);
}

/**
 * @brief TComboBoxDelegate::setModelData
 * @param editor
 * @param model
 * @param index
 */
void TComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox *>(editor);
    QString str = comboBox->currentText();
    model->setData(index,str,Qt::EditRole);
}

/**
 * @brief TComboBoxDelegate::updateEditorGeometry
 * @param editor
 * @param option
 * @param index
 */
void TComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
