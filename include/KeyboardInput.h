#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "GameEntity.h"
#include "GameState.h"

// Third party
#include <SDL2/SDL.h>

class KeyboardInput
{
    public:
        KeyboardInput(Uint8 goUpKey, Uint8 goDownKey, GameEntity* entity, GameState* gameState);
        ~KeyboardInput();

        void UserInput();

    private:
        SDL_Event keyboardEvent;
};

#endif