#pragma once

#include <SDL2/SDL.h>
#include "model.h"
#include "view.h"


class Control {
private:
    View& view;
    const Uint8* key_state;
public:
    void handleInput();
    Control(View& view);
};
