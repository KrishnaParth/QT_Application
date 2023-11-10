#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H

#include <QObject>
#include<QItemDelegate>
#include<QComboBox>
#include<QPalette>

class combobox_delegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit combobox_delegate(QObject *parent = 0);

    /* view will call create editor and make editor for the deligate */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /* Modify data in current cell */
    void setEditorData(QWidget *editor,const QModelIndex &index)const;

    /* Returns data back in model */
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;

private:
    QStringList list = {"M","F"};

};

#endif // COMBOBOX_DELEGATE_H
