#ifndef GAMESTATE_H
#define GAMESTATE_H

// Global struct for Pong!

struct GameState
{;
    float movementSpeed;
    float velocity;
    float ballSpeed;
    int ballXDirection;
    int ballYDirection;

    int leftScore, rightScore;
};

#endif