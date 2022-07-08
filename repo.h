#pragma once

#include "domain.h"
#include <sstream>
#include <fstream>

class FileRepo{
private:
    string filename;
    vector<Task> tasks;

    void load();
    void save();

public:
    FileRepo(string filename): filename{filename}{
        load();
    }

    void validateId(int id);

    void add(Task t);

    vector<Task>& get_all();

    void change(int ind,string state);
};

class DuplicatedIdException{
private:
    string message;
public:
    DuplicatedIdException(string message):message{message}{}

    string getMessage(){
        return message;
    }
};

void test_repo();

int to_nr(string nr);

