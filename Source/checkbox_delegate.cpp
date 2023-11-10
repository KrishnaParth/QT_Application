#include "checkbox_delegate.h"

checkbox_delegate::checkbox_delegate(QObject *parent):QItemDelegate(parent)
{

}

void checkbox_delegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    drawDisplay(painter,option,option.rect,index.model()
                ->data( index, Qt::DisplayRole )
                .toBool()?QString("      ")
                          .append(tr("Yes")):QString("      ")
                          .append(tr("No")));

//    drawCheck(painter,option,option.rect,index.model()->data(index,Qt::DisplayRole)
//             .toBool()?Qt::Checked:Qt::Unchecked);


    drawFocus(painter,option,option.rect);
}


QWidget *checkbox_delegate::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &/* option */,
                                             const QModelIndex &/* index */) const
{
    x_check_box = new QCheckBox( parent );
    x_check_box->setCheckable( true );
    x_check_box->setEnabled( true );
    x_check_box->setCheckState(  Qt::Unchecked );

    QObject::connect( x_check_box,
                      SIGNAL( toggled(bool) ),
                      this,
                      SLOT( setData(bool) ) );

    return( x_check_box );
}


void checkbox_delegate::setEditorData( QWidget *editor,
                                           const QModelIndex &index) const
{
    int i_val = index.model()->data( index, Qt::EditRole ).toInt();

    (static_cast<QCheckBox*>( editor ))->setChecked( i_val );
}


void checkbox_delegate::setModelData( QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const
{
    model->setData( index, (int)(static_cast<QCheckBox*>( editor )->isChecked() ) );
}


void checkbox_delegate::updateEditorGeometry( QWidget *editor,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &/* index */) const
{
    editor->setGeometry( option.rect );
}

void checkbox_delegate::setData( bool /*val*/ )
{
    emit commitData( x_check_box );
}
