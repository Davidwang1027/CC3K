#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include <iostream>
#include <vector>
#include <iostream>
#include "state.h"


class TextDisplay : public Observer <State>{
    std::vector<std::vector<char>> theDisplay;
public:
    void notify(Subject<State>& whoNotified) override;
    friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};


#endif
