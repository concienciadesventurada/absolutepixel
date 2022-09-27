#include "KeyboardInput.h"

// TWO ERRORS in gameState: expression must have integral or unscoped enum typeC/C++(2140). Uploading backup to github previous serious refactoring to clean up main function and allow multiple players

KeyboardInput::KeyboardInput(Uint8 goUpKey, Uint8 goDownKey, GameEntity* entity, GameState* gameState)
{
    if (keyboardEvent.type == SDL_KEYDOWN)
    {
        int entityPosX = entity->GetSprite().GetPositionX();
        int entityPosY = entity->GetSprite().GetPositionY();

        if (keyboardEvent.key.keysym.sym == goUpKey)
        {
            entity -= gameState->movementSpeed;
            entity->SetPosition(entityPosX, entityPosY);
        }
        if (keyboardEvent.key.keysym.sym == goDownKey)
        {
            entity += gameState->movementSpeed;
            entity->SetPosition(entityPosX, entityPosY);
        }

    }

}

KeyboardInput::~KeyboardInput()
{

}
