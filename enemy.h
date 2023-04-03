#include "entity.h"

class Enemies : public Entity {
    public:
        virtual void attack(Entity& whodef) override;
        virtual void move() override;
};