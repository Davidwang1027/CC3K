#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename Statetype> class Observer;

template <typename Statetype> class Subject{
    std::vector<Observer*> observers;
    T type;
public:
    virtual void notifyObservers();
    virtual void attach(Observer<Statetype>* o);
    void setState();
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
void Subject<Statetype>::setType()
#endif
