#ifndef ENEMYRESPONSECOMPONENT_H
#define ENEMYRESPONSECOMPONENT_H

#include "common/component.h"
#include "common/gameobject.h"

class EnemyResponseComponent : public Component {
public:
    EnemyResponseComponent(GameObject *gameObject);
    void tick(float seconds) override;
    void respond();
};

#endif // ENEMYRESPONSECOMPONENT_H
