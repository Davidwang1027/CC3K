#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename T> class Observer;

template <typename T> class Subject{
    std::vector<Observer*> observers;
    T type;
public:
    virtual void notifyObservers();
    virtual void attach(Observer<T>* o);
    void setType();
    T getType();
};

template <typename T>
void Subject<T>::notifyObservers(){
    for (auto o : observers){
        o->notify(*this);
    }
}

template <typename T>
void Subject<T>::attach(Observer<T>* o){
    observers.push_back(o);
}

#endif
