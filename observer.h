#ifndef OBSERVER_H
#define OBSERVER_H

template <typename Statetype> class Subject;
template <typename Statetype> class Observer{
public:
    virtual void notify(Subject<Statetype>& whoNotified) = 0;
};

#endif
