#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include <vector>

class TextDisplay : public Observer{
    void notify(Subject& whoNotified) override;
    std::vector<std::vector<char>> theDisplay;

};


#endif
