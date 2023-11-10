#include "table_model.h"

table_model::table_model():QAbstractTableModel() //QObject *parent = 0
{

}

int table_model::rowCount(const QModelIndex &) const
{
     return stringitem.count();
}

int table_model::columnCount(const QModelIndex &) const
{
    return stringitem.count();



}

QVariant table_model::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole || index.column() == 1 || index.column() ==2) {
        return QVariant::fromValue(stringitem);
    }

    else if (role == Qt::DisplayRole || index.column() == 3 )
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();

        //gender = new QComboBox;
//        gender->setItemText(index,"M");
//        gender->setItemText(index,"F");
        gender->addItem("M",QVariant::fromValue(stringitem));
        gender->addItem("F",QVariant::fromValue(stringitem));

    }

    else
    {
        return QVariant::fromValue(intitem);
    }
}

bool table_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && ( role == Qt::DisplayRole)) {

        switch (index.column()) {
        case 1:
        {
            stringitem = value.value<QString>();
            break; }
        case 2:
        {
            stringitem = value.value<QString>();
            break; }
        case 3:
        {
            stringitem = value.value<QString>();
            break; }
        default:
            break;
        }

        emit dataChanged(index,index);
        return true;

//        stringitem[index.row()+1][1] = value.toString();
//        stringitem[index.row()+1][2] = value.toString();
//        stringitem[index.row()+1][3] = value.toString();

    }
    else if(index.isValid() && ( role == Qt::EditRole)) {

        switch (index.column()) {
        case 0:
        {
            intitem = value.value<int>();
            break; }
        case 4:
        {
            intitem = value.value<int>();
            break; }
        case 5:
        {
            intitem = value.value<int>();
            break; }
        default:
            break;
        }

        emit dataChanged(index,index);
        return true;

//        stringitem[index.row()+1][0] = value.toInt();  //READ index operator
//        stringitem[index.row()+1][4] = value.toInt();
//        stringitem[index.row()+1][5] = value.toInt();
    }
}

Qt::ItemFlags table_model::flags(const QModelIndex &index) const
{
    if(!index.isValid()) { return 0; }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
