#ifndef TSPINBOXDELEGATE_H
#define TSPINBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class TSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TSpinBoxDelegate(QObject *parent = nullptr);
    ~TSpinBoxDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


inline TSpinBoxDelegate::~TSpinBoxDelegate() {}

#endif // TSPINBOXDELEGATE_H
