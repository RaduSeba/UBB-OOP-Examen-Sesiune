

#include "service.h"
#include <algorithm>

void Service::add(int id, string title, vector<string> prog, string state) {
    Task::validate(id,title,prog,state);
    repo.validateId(id);
    repo.add(Task(id,title,prog,state));
    notify();
}



vector<Task> &Service::get_all_ent() {
    return repo.get_all();
}

void Service::validateIdd(int id) {
    repo.validateId(id);
}

vector<Task> Service::filter(string crit) {
    vector<Task> rez;
    rez.clear();

    for(auto& task: repo.get_all()){
      
        for (auto& el : task.getProgrammers())
        {
            if (el.find(crit) != -1)
            {
                rez.push_back(task);
            }
        }
        
        
        /* string name=task.getTitle();
        if(name.find(crit)!=-1){
            rez.push_back(task);
        }*/
    }

    return rez;
}

void Service::changeState(int ind, string new_state) {
    repo.change(ind,new_state);
    notify();
}

void test_service(){
    auto rp=FileRepo{"text.txt"};
    auto srv=Service{rp};
    assert(srv.get_all_ent().size()==5);

    vector<string> prog;
    prog.push_back("Seba");
    prog.push_back("Stanis");

    srv.add(10,"Soft",prog,"open");
    assert(srv.get_all_ent().size()==6);

    try{
        srv.add(1,"Soft",prog,"open");
        assert(false);
    } catch(DuplicatedIdException& de){
        assert(true);
    }

    try{
        srv.add(1,"",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        srv.add(1,"Soft",prog,"");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        prog.push_back(prog[0]);
        prog.push_back(prog[0]);
        prog.push_back(prog[0]);
        srv.add(1,"Soft",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        prog.clear();
        srv.add(1,"Soft",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }



    auto rez=srv.filter("Seba");

    assert(rez.size()==4);

}