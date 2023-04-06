#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include <iostream>
#include <vector>
#include <iostream>
#include "state.h"


class TextDisplay : public Observer <State>{
    size_t row;
    size_t col;
    std::vector<std::vector<char>> theDisplay;
public:
    TextDisplay(size_t row, size_t col);
    void notify(Subject<State>& whoNotified) override;
    friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};


#endif
