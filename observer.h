#pragma once
#include <vector>

using namespace std;

class Observer{
public:
    virtual void alert()=0;
};

class Observable{
private:
    vector<Observer*> obs;
public:
    void addObserver(Observer* ob){
        obs.push_back(ob);
    }
    void notify(){
        for(auto it: obs){
            it->alert();
        }
    }
    void removeObs(Observer* ob) {
        obs.erase(remove(obs.begin(),obs.end(),ob),obs.end());
    }
};

