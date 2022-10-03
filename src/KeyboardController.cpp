#include "KeyboardController.h"

// TWO ERRORS in gameState: expression must have integral or unscoped enum typeC/C++(2140). Uploading backup to github previous serious refactoring to clean up main function and allow multiple players

KeyboardController::KeyboardController(SDL_KeyCode goUpKey, SDL_KeyCode goDownKey)
{
    m_goUpKey = goUpKey;
    m_goDownKey = goDownKey;
}

void KeyboardController::UpdateKeyboardEvent(SDL_Event &event, GameEntity* entity, GameState* gameState)
{
    if (event.type == SDL_KEYDOWN)
    {
        int entityPosX = entity->GetSprite().GetPositionX();
        int entityPosY = entity->GetSprite().GetPositionY();

        if (event.key.keysym.sym == m_goUpKey)
        {
            entityPosY -= gameState->movementSpeed;
            entity->SetPosition(entityPosX, entityPosY);
        }
        else if (event.key.keysym.sym == m_goDownKey)
        {
            entityPosY += gameState->movementSpeed;
            entity->SetPosition(entityPosX, entityPosY);
        }
    }

//    if (event.type == SDL_KEYUP)
//    {
//        int entityPosX = entity->GetSprite().GetPositionX();
//        int entityPosY = entity->GetSprite().GetPositionY();
//
//        if (event.key.keysym.sym == m_goUpKey)
//        {
//            gameState->movementSpeed = 0;
//        }
//        else if (event.key.keysym.sym == m_goDownKey)
//        {
//            gameState->movementSpeed = 0;
//        }
//    }
}
