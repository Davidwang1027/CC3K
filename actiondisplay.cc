#include "actiondisplay.h"
#include "subject.h"
void ActionDisplay::notify(Subject<State>& whoNotified){
    display.emplace_back(whoNotified.getState().action);
}

std::ostream& operator<<(std::ostream& out, const ActionDisplay& ad){
    for (auto s : ad.display){
        out << s << std::endl;
    }
    return out;
}
