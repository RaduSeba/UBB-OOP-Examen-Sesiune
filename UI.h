#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTableView>
#include <QSpinBox>
#include "service.h"
#include "MyListModel.h"

class Window: public QWidget, public Observer{
    //Clasa pentru ferestrele care se deschid
private:
    string title;
    Service& srv;
    QVBoxLayout* lyMain=new QVBoxLayout;
    QListWidget* lst_wdg;
    QPushButton* open;
    QPushButton* close;
    QPushButton* inprogress;

    void initGUI();
    void connectSignals();
    void reloadList(vector<Task> all);

public:
    void alert() override;
    Window(Service& srv,string tit):srv{srv},title{tit}{
        srv.addObserver(this);
        setWindowTitle(QString::fromStdString(title));
        initGUI();
        connectSignals();
        reloadList(srv.get_all_ent());
        show();
    }
    ~Window(){
        srv.removeObs(this);
    }
};

class GUI:public QWidget,public Observer{
    //Clasa GUI 
private:
    Service& srv;
    vector<Task> displayed;
    QHBoxLayout* ly_main=new QHBoxLayout;
    QTableWidget* tb_wdg;

    QTableView* tb_view;
    MyTableModel* tb_model;

    QLineEdit* search;
    QLineEdit* txt_id;
    QLineEdit* txt_desc;
    QLineEdit* txt_state;
    QLineEdit* txt_prog1;
    QLineEdit* txt_prog2;
    QLineEdit* txt_prog3;
    QLineEdit* txt_prog4;
    QPushButton* btna;
    Window* wopen;
    Window* wclose;
    Window* wprogress;

    void initGUI();
    void connectSignals();
    void reloadList(vector<Task>& all);

public:
    void alert() override;
    GUI(Service& srv):srv{srv}{
        srv.addObserver(this);
        initGUI();
        tb_model=new MyTableModel{srv.get_all_ent()};
        displayed=srv.get_all_ent();
        tb_view->setModel(tb_model);
        connectSignals();
        reloadList(srv.get_all_ent());
        wopen=new Window{srv,"open"};
        wclose=new Window{srv,"closed"};
        wprogress=new Window{srv,"inprogress"};
    }
    ~GUI(){
        delete wopen;
        delete wclose;
        delete wprogress;
        srv.removeObs(this);
    }
};

