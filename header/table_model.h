#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QObject>
#include<QAbstractTableModel>
#include<QComboBox>

class table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    table_model();  //QObject *parent = 0

    /* checking data before edit */

   // StringListModel(const QStringList &strings, QObject* parent = 0)
     //   :QAbstractListModel(parent),stringList(strings) {} //subclassing QAbstractListModel : defines sensible
                                                           //default behaviour for list models
                                                           //dont store data,merely presents interface that view uses to access data

    int rowCount(const QModelIndex &parent) const override; //returns no of rows              = QModelIndex()
    int columnCount(const QModelIndex &parent ) const override;
    QVariant data (const QModelIndex &index, int role) const override;   //return data at index  =Qt::DisplayRole
    bool setData(const QModelIndex &index, const QVariant &value, int role ) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

     QComboBox * gender;

private:
   QString stringitem;
    QString intitem;
    QStringList list = {"M","F"};


};



#endif // TABLE_MODEL_H
