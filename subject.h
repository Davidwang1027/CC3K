#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
class Subject{
    std::vector<Observer*> observers;
public:
    virtual void notifyObservers() = 0;
    virtual void attach(Observer* o) = 0;
};

void Subject::notifyObservers(){
    for (auto o : observers){
        o->notify();
    }
}

void Subject::attach(Observer* o){
    observers.push_back(o);
}

#endif
