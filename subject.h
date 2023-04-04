#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename Statetype> class Observer;
template <typename Statetype> class Subject{
    std::vector<Observer<Statetype>*> observers;x
        Statetype state;
public:
    virtual void notifyObservers();
    virtual void attach(Observer<Statetype>* o);
    void setState(Statetype);
    Statetype getState();
};

template <typename Statetype>
void Subject<Statetype>::notifyObservers(){
    for (auto o : observers){
        o->notify(*this);
    }
}

template <typename Statetype>
void Subject<Statetype>::attach(Observer<Statetype>* o){
    observers.push_back(o);
}

template <typename Statetype>
void Subject<Statetype>::setState(Statetype newstate){
    state = newstate;
}

template <typename Statetype>
Statetype Subject<Statetype>::getState(){
    return state;
}

#endif
