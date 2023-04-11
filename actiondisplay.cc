#include "actiondisplay.h"
#include "subject.h"
void ActionDisplay::notify(Subject<State>& whoNotified){
    if (whoNotified.getState().action != ""){
        display.emplace_back(whoNotified.getState().action);
    }
}

std::ostream& operator<<(std::ostream& out, const ActionDisplay& ad){
    for (auto s : ad.display){
        out << s;
    }
    return out << std::endl;
}
