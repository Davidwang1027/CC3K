#ifndef ACTIONDISPLAY_H
#define ACTIONDISPLAY_H
#include "observer.h"
#include <iostream>
#include <vector>
#include <string>
#include "state.h"

class ActionDisplay : public Observer<State>{
    std::vector<std::string> display;
public:
    void notify(Subject<State>& whoNotified) override;
    friend std::ostream& operator<<(std::ostream& out, const ActionDisplay& ad);
    void clear(){
        display.clear();
    }
};



#endif
