#ifndef CHECKBOX_DELEGATE_H
#define CHECKBOX_DELEGATE_H

#include <QObject>
#include<QItemDelegate>
#include<QCheckBox>


class checkbox_delegate : public QItemDelegate
{
    Q_OBJECT

public:
   checkbox_delegate(QObject *parent = 0);
    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

    void setEditorData( QWidget *editor, const QModelIndex &index ) const;

    void setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

/* ------------- Public Members ------------- */
public:
    mutable QCheckBox * x_check_box;


/* ------------- Private Slots ------------- */
private slots:
    void setData(bool);




//public:
//   explicit checkbox_delegate(QObject *parent);

//    /* view will call create editor and make editor for the deligate */
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//    /* Modify data in current cell */
//    void setEditorData(QWidget *editor,const QModelIndex &index)const;

//    /* Returns data back in model */
//    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;

//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;
};

#endif // CHECKBOX_DELEGATE_H
