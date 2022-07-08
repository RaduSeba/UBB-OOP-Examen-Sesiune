

#include "repo.h"

int to_nr(string s){
    int rez=0;
    int sign=1;
    if(s[0]=='-'){
        sign=-1;
        s.erase(s.begin());
    }
    for(auto& ch:s){
        if(!('0'<=ch && ch<='9')){
            throw ValidationException("Id-ul trebuie sa fie intreg");
        }
        rez=rez*10+(ch-'0');
    }
    return rez*sign;
}

void FileRepo::validateId(int id) {
    bool found=false;
    for(auto& task: tasks){
        if(task.getId()==id){
            found=true;
            break;
        }
    }
    if(found){
        throw DuplicatedIdException("Nu sunt permise 2 id-uri identice");
    }
}

void FileRepo::load() {
    ifstream fin(filename);
    string line;
    while(getline(fin,line)){
        if(line.empty()){
            continue;
        }
        auto ss=stringstream(line);
        vector<string> elems;
        string elem;
        while(getline(ss, elem,';')){
            elems.push_back(elem);
        }
        ss=stringstream(elems[2]);
        vector<string>prog;
        while(getline(ss,elem,',')){
            prog.push_back(elem);
        }
        auto t=Task(to_nr(elems[0]),elems[1],prog,elems[3]);
        add(t);
    }
}

void FileRepo::add(Task t) {
    tasks.push_back(t);
    save();
}

void FileRepo::save() {
    ofstream fout(filename);
    for(auto& task:tasks){
        fout<<task.getId()<<";"<<task.getTitle()<<";";
        auto all=task.getProgrammers();
        for(auto& it:all){
            if(it!=*all.begin()){
                fout<<',';
            }
            fout<<it;
        }
        fout<<';';
        fout<<task.getState()<<"\n";
    }
}

vector<Task> &FileRepo::get_all() {
    return tasks;
}

void FileRepo::change(int ind, string state) {
    tasks[ind].setState(state);
    save();
}

void test_repo(){
    auto fr=FileRepo{"text.txt"};
    auto all=fr.get_all();
    assert(all.size()==4);

    vector<string> prog;
    prog.push_back("Alex Sirbu");
    prog.push_back("Seba");

    fr.add(Task(8, "OOP", prog, "open"));


      all=fr.get_all();
     assert(all.size()==5);

    try{
        fr.validateId(1);
        assert(false);
    } catch(DuplicatedIdException& dp){
        assert(true);
    }

    assert(to_nr("13")==13);
    assert(to_nr("-13")==-13);
}