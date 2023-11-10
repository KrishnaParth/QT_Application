#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>
#include<QItemDelegate>
#include<QModelIndex>
#include<QSize>
#include<QSpinBox>
#include<QWidget>
#include<QComboBox>

class delegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit  delegate (QObject *parent = 0);

    /* view will call create editor and make editor for the deligate */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /* Modify data in current cell */
    void setEditorData(QWidget *editor,const QModelIndex &index)const;

    /* Returns data back in model */
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;

private:

};

#endif // DELEGATE_H
