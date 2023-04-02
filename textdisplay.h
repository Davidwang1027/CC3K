#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include <iostream>
#include <vector>

class TextDisplay : public Observer{
    std::vector<std::vector<char>> theDisplay;
public:
    void notify(Subject& whoNotified) override;
    friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};


#endif
