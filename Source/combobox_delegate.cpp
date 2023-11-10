#include "combobox_delegate.h"

combobox_delegate::combobox_delegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *combobox_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

        QComboBox *gender = new QComboBox(parent);
        gender->addItems(list);
        gender->setStyleSheet("QComboBox {background-color : grey ;}");
//        QPalette pal ;
//        pal.setBrush(QPalette::Base,Qt::transparent );
//        gender->setPalette(pal);

        return gender;

}

void combobox_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str =index.model()->data(index,Qt::EditRole).toString();
    QComboBox * gender = static_cast<QComboBox*>(editor);

    int idx = list.indexOf(str);
    gender->setCurrentIndex(idx);
    connect(gender, QOverload<int>::of(&QComboBox::currentIndexChanged),this,
            std::bind(&QAbstractItemDelegate::commitData,const_cast<combobox_delegate*>(this),gender));
}

void combobox_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *gender = qobject_cast<QComboBox*>(editor);
    QString val = gender->currentText();
    model->setData(index,val,Qt::EditRole);
}

void combobox_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
