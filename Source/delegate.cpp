#include "delegate.h"

delegate::delegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
      QSpinBox *editor = new QSpinBox(parent);

      if(index.column() == 5){
          editor->setMinimum(0);
          editor->setMaximum(INT_MAX);
      }
      if(index.column() == 4){
          editor->setMinimum(0);
          editor->setMaximum(150);
      }
      return editor;
}

void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

      int value = index.model()->data(index,Qt::EditRole).toInt();
      QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
      spinbox->setValue(value);

}

void delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->interpretText();
    int value = spinbox->value();
    model->setData(index,value,Qt::EditRole);

}

void delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
