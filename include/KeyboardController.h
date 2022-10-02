#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "GameEntity.h"
#include "GameState.h"

// Third party
#include <SDL2/SDL.h>

class KeyboardController
{
    public:
        KeyboardController(SDL_KeyCode goUpKey, SDL_KeyCode goDownKey);
        ~KeyboardController();

        void UpdateKeyboardEvent(SDL_Event &event, GameEntity* entity, GameState* gameState);

    private:
        Uint8 m_goUpKey, m_goDownKey;
};

#endif