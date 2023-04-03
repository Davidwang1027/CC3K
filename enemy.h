#include "entity.h"

class Enemy : public Entity {
    public:
        virtual void attack(Entity& whodefend) override;
        virtual void move() override;
};
