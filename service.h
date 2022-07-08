#pragma once
#include "repo.h"
#include "observer.h"

class Service:public Observable{
private:
    FileRepo& repo;
public:
    Service(FileRepo& rp): repo{rp}{}

    void add(int id,string title,vector<string> prog,string state);

    vector<Task>& get_all_ent();

    void validateIdd(int id);

    vector<Task> filter(string crit);

    void changeState(int ind,string new_state);
};

void test_service();
