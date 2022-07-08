#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <assert.h>

using namespace std;

class Task{
    //initializare clasa Task
private:
    int id;
    string title;
    vector<string> program;
    string state;
public:
    Task(int id,string title,vector<string>& program,string state):id{id},title{title},program{program},state{state}{}

    //functia care returneaza id ul Taskului
    int getId() const;
    //functia care returneaza titlul ul Taskului
    string getTitle() const;
    //functia care returneaza vectorul cu programatorii Taskului
    vector<string> getProgrammers() const;
    //functia care returneaza starea Taskului
    string getState() const;
    //functia care seteaza starea Taskului
    void setState(string new_state);


    //functia de validare a Taskului
    static void validate(int id,string title,vector<string>& program,string state);

};


//Teste pentru domain
void test_domain();

//clasa de Validare
class ValidationException{
private:
    string message;
public:
    ValidationException(string message):message{message}{}

    string getMessage(){
        return message;
    }
};


