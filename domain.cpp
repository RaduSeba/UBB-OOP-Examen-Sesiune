
#include "domain.h"

int Task::getId() const {
    return id;
}

string Task::getTitle() const {
    return title;
}

vector<string> Task::getProgrammers() const {
    return program;
}

string Task::getState() const {
    return state;
}

void Task::validate(int id, string title, vector<string> &program, string state) {
    string exc="";
    if(title==""){
        exc+="Titlul nu poate fi vid\n";
    }
    if(program.empty() || program.size()>4){
        exc+="Orice task poate avea intre 1 si 4 programatori\n";
    }
    if(state==""){
        exc+="Starea nu poate fi vida\n";
    }
    if(state!="open" && state!="closed" && state!="inprogress"){
        exc+="Starea nu poate fi doar open, closed sau inprogress\n";
    }
    if(exc!=""){
        throw ValidationException(exc);
    }
}

void Task::setState(string new_state) {
    state=new_state;
}

void test_domain(){
    vector<string> prog;
    prog.push_back("Alex Sirbu");
    prog.push_back("Daciana Roman");
    auto t=Task(1,"Soft",prog,"open");

    assert(t.getId()==1);
    assert(t.getTitle()=="Soft");
    assert(t.getProgrammers()==prog);
    assert(t.getState()=="open");

    Task::validate(1,"Soft",prog,"open");

    try{
        Task::validate(1,"",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        Task::validate(1,"Soft",prog,"");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        prog.push_back(prog[0]);
        prog.push_back(prog[0]);
        prog.push_back(prog[0]);
        Task::validate(1,"Soft",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }

    try{
        prog.clear();
        Task::validate(1,"Soft",prog,"open");
        assert(false);
    } catch(ValidationException& ve){
        assert(true);
    }
}