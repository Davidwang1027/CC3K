#include "player.h"

class Decorator : public Player {
    protected:
        Player *component;
    public:
        Decorator(Player *component) : component{component} {};
        virtual ~Decorator() { delete component; };
};
