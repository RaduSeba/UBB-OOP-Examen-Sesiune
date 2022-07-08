#pragma once


#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class MyTableModel: public QAbstractTableModel{
private:
    vector<Task> tasks;
public:
    MyTableModel(vector<Task> tasks):tasks{tasks}{}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return tasks.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override{
        return 4;
    }

    QVariant data(const QModelIndex& ind, int role=Qt::DisplayRole) const override{
        //qDebug()<<"Here";
        if(role==Qt::DisplayRole){
            if(ind.column()==0){
                return QString::number(tasks[ind.row()].getId());
            } else if(ind.column()==1){
                return QString::fromStdString(tasks[ind.row()].getTitle());
            } else if(ind.column()==2){
                return QString::fromStdString(tasks[ind.row()].getState());
            } else if(ind.column()==3){
                return QString::number(tasks[ind.row()].getProgrammers().size());
            }
        }
        return QVariant{};
    }

    void setTasks(vector<Task>& nw){
        tasks=nw;
        auto up= createIndex(0,0);
        auto down= createIndex(rowCount(), columnCount());
        emit dataChanged(up,down);
        emit layoutChanged();
    }



    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            if (section == 0)
                return "ID";
            if (section == 1)
                return "DENUMIRE";
            if (section == 2)
                return "STARE";
            if (section == 3)
                return "NR PROGRAMATORI";
        }
        return QVariant();
    }

};

