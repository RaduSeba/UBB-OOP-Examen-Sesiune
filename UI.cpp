
#include "UI.h"

void GUI::initGUI() {
    setLayout(ly_main);
    
    tb_view=new QTableView;
    ly_main->addWidget(tb_view);


    QWidget* wdg_right=new QWidget;
    QVBoxLayout* ly_right=new QVBoxLayout;
    wdg_right->setLayout(ly_right);

    QWidget* form_wdg=new QWidget;
    QFormLayout* form_lay=new QFormLayout;
    form_wdg->setLayout(form_lay);

    QLabel* lId=new QLabel("Id");
    QLabel* lT=new QLabel("Titlu");
    QLabel* lS=new QLabel("Starea");
    QLabel* lProg1=new QLabel("Programator1");
    QLabel* lProg2=new QLabel("Programator2");
    QLabel* lProg3=new QLabel("Programator3");
    QLabel* lProg4=new QLabel("Programator4");

    txt_id=new QLineEdit;
    txt_state=new QLineEdit;
    txt_desc=new QLineEdit;
    txt_prog1=new QLineEdit;
    txt_prog2=new QLineEdit;
    txt_prog3=new QLineEdit;
    txt_prog4=new QLineEdit;

    form_lay->addRow(lId,txt_id);
    form_lay->addRow(lT,txt_desc);
    form_lay->addRow(lS,txt_state);
    form_lay->addRow(lProg1,txt_prog1);
    form_lay->addRow(lProg2,txt_prog2);
    form_lay->addRow(lProg3,txt_prog3);
    form_lay->addRow(lProg4,txt_prog4);


    QLabel* l = new QLabel("Cauta string programator:");
    search = new QLineEdit;
   // form_lay->setVerticalSpacing(100);
    form_lay->addRow(l, search);

    ly_right->addWidget(form_wdg);

    btna=new QPushButton("Add");
    ly_right->addWidget(btna);

    /*QLabel* l = new QLabel("Cauta string programator:");
    search=new QLineEdit;
    ly_right->addWidget(search);*/

    ly_main->addWidget(wdg_right);


}

void GUI::connectSignals() {
    

    QObject::connect(tb_view->selectionModel(),&QItemSelectionModel::selectionChanged,[=](){
        if(tb_view->selectionModel()->selectedIndexes().empty()){
            txt_id->setText("");
            txt_desc->setText("");
            txt_state->setText("");
            txt_prog1->setText("");
            txt_prog2->setText("");
            txt_prog3->setText("");
            txt_prog4->setText("");
            return;
        }
        auto sel=tb_view->selectionModel()->selectedIndexes().at(0);
        int row=sel.row();
        auto elem=displayed[row];
        txt_id->setText(QString::number(elem.getId()));
        txt_desc->setText(QString::fromStdString(elem.getTitle()));
        txt_state->setText(QString::fromStdString(elem.getState()));

        auto asa=elem.getProgrammers();
        if(asa.size()>=1) {
            txt_prog1->setText(QString::fromStdString(asa[0]));
        } else txt_prog1->setText("");
        if(asa.size()>=2){
            txt_prog2->setText(QString::fromStdString(asa[1]));
        } else txt_prog2->setText("");
        if(asa.size()>=3){
            txt_prog3->setText(QString::fromStdString(asa[2]));
        } else txt_prog3->setText("");
        if(asa.size()>=4){
            txt_prog4->setText(QString::fromStdString(asa[3]));
        } else txt_prog4->setText("");
    });

    QObject::connect(btna,&QPushButton::clicked,[=](){
        try{
            int id=to_nr(txt_id->text().toStdString());
            string desc=txt_desc->text().toStdString();
            string state=txt_state->text().toStdString();

            vector<string> prog;

            string prog1=txt_prog1->text().toStdString();
            if(prog1!=""){
                prog.push_back(prog1);
            }

            string prog2=txt_prog2->text().toStdString();
            if(prog2!=""){
                prog.push_back(prog2);
            }

            string prog3=txt_prog3->text().toStdString();
            if(prog3!=""){
                prog.push_back(prog3);
            }

            string prog4=txt_prog4->text().toStdString();
            if(prog4!=""){
                prog.push_back(prog4);
            }

            Task::validate(id,desc,prog,state);
            srv.validateIdd(id);
            srv.add(id,desc,prog,state);
            int row=tb_model->rowCount(QModelIndex());
            tb_model->insertRows(row,1,QModelIndex());
            reloadList(srv.get_all_ent());
        } catch(ValidationException& ve){
            QMessageBox::warning(this,"Warning",QString::fromStdString(ve.getMessage()));
        } catch(DuplicatedIdException& ex){
            QMessageBox::warning(this,"Warning",QString::fromStdString(ex.getMessage()));
        }
    });

    QObject::connect(search,&QLineEdit::editingFinished,[=](){
        if(search->text()==""){
            reloadList(srv.get_all_ent());
        } else {
            displayed=srv.filter(search->text().toStdString());
            reloadList(displayed);
        }
    });

}

void GUI::reloadList(vector<Task>& all) {
    sort(all.begin(),all.end(),[](Task& t1,Task& t2){
        return t1.getState() > t2.getState();
    });
    
    displayed=all;
    tb_model->setTasks(all);

    
}

void GUI::alert() {
    reloadList(srv.get_all_ent());
}

void Window::initGUI() {
    setLayout(lyMain);

    lst_wdg=new QListWidget;
    lyMain->addWidget(lst_wdg);

    QWidget* wdg_down=new QWidget;
    QHBoxLayout* lay_down=new QHBoxLayout;
    wdg_down->setLayout(lay_down);

    open=new QPushButton("Open");
    close=new QPushButton("Close");
    inprogress=new QPushButton("In progress");

    lay_down->addWidget(open);
    lay_down->addWidget(close);
    lay_down->addWidget(inprogress);

    lyMain->addWidget(wdg_down);
}

void Window::connectSignals() {
    QObject::connect(open,&QPushButton::clicked,[=](){
        if(lst_wdg->selectedItems().empty()){
            QMessageBox::warning(this,"Warning","Nu ati selectat nimic");
            return;
        }
        auto sel=lst_wdg->selectedItems().at(0);
        int id=sel->data(Qt::UserRole).toInt();
        int index=0;
        int ret;
        for(auto& it:srv.get_all_ent()){
            if(it.getId()==id){
                ret=index;
            }
            ++index;
        }
        srv.changeState(ret,"open");
    });

    QObject::connect(close,&QPushButton::clicked,[=](){
        if(lst_wdg->selectedItems().empty()){
            QMessageBox::warning(this,"Warning","Nu ati selectat nimic");
            return;
        }
        auto sel=lst_wdg->selectedItems().at(0);
        int id=sel->data(Qt::UserRole).toInt();
        int index=0;
        int ret;
        for(auto& it:srv.get_all_ent()){
            if(it.getId()==id){
                ret=index;
            }
            ++index;
        }
        srv.changeState(ret,"closed");
    });

    QObject::connect(inprogress,&QPushButton::clicked,[=](){
        if(lst_wdg->selectedItems().empty()){
            QMessageBox::warning(this,"Warning","Nu ati selectat nimic");
            return;
        }
        auto sel=lst_wdg->selectedItems().at(0);
        int id=sel->data(Qt::UserRole).toInt();
        int index=0;
        int ret;
        for(auto& it:srv.get_all_ent()){
            if(it.getId()==id){
                ret=index;
            }
            ++index;
        }
        srv.changeState(ret,"inprogress");
    });
}

void Window::reloadList(vector<Task> all) {
    lst_wdg->clear();
    for(auto& it: all){
        if(it.getState()==title){
            QListWidgetItem *itm=new QListWidgetItem(QString::fromStdString(it.getTitle()));
            itm->setData(Qt::UserRole,QString::number(it.getId()));
            lst_wdg->addItem(itm);
        }
    }
}

void Window::alert() {
    reloadList(srv.get_all_ent());
}