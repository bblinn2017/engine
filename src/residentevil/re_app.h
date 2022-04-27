#ifndef RE_APP_H
#define RE_APP_H

#include "common/application.h"
#include "screens/gamescreen.h"

enum re_screen_t {GAME};

class ReApp : public Application {
public:
    ReApp();

    void tick(float seconds) override;
    void reset() override;
};

#endif // RE_APP_H
