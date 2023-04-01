#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
class Subject{
    std::vector<Observer*> observers;
public:
    virtual void notifyObservers();
    virtual void attach(Observer* o);
};

void Subject::notifyObservers(){
    for (auto o : observers){
        o->notify(*this);
    }
}

void Subject::attach(Observer* o){
    observers.push_back(o);
}

#endif
