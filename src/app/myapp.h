#ifndef MYAPP_H
#define MYAPP_H

#include "common/application.h"
#include "screens/playscreen.h"
#include "screens/mainscreen.h"

enum MyScreenType {MAIN,PLAY};

class MyApp : public Application {
public:
    MyApp();

    void tick(float seconds) override;
    void reset() override;
};

#endif // MYAPP_H
