#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "common/system.h"
#include "components/drawcomponent.h"

class DrawSystem : public System {
public:
    DrawSystem();

    void draw();
};

#endif // DRAWSYSTEM_H
