#include "Level.hpp"

namespace  barrio
{
    void Level::CreateLevel(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts)
    {
        this->renderer = renderer;
        this->physicsWorld = physicsWorld;
        this->camera = camera;
        this->texts = texts;
    }
    
    void Level::handleInputPlayer(Character& player)
    {        
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if (currentKeyStates[player.movements[Sprite::Movement::UP]] )
        {
            physicsWorld->getBody(player.getName())->SetLinearVelocity({0.0f, -vel});
            player.playAnimation(consts::MOVEMENT_WALKING, consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::DOWN]] )
        {
            physicsWorld->getBody(player.getName())->SetLinearVelocity({0.0f, vel});
            player.playAnimation(consts::MOVEMENT_WALKING, consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::LEFT]] )
        {
            player.setSide(Glob::Side::LEFT_SIDE);
            physicsWorld->getBody(player.getName())->SetLinearVelocity({-vel, 0.0f});
            player.playAnimation(consts::MOVEMENT_WALKING, consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::RIGHT]] )
        {
            player.setSide(Glob::Side::RIGHT_SIDE);
            physicsWorld->getBody(player.getName())->SetLinearVelocity({vel, 0.0f});
            player.playAnimation(consts::MOVEMENT_WALKING, consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::PUNCH]] )
        {
            physicsWorld->getBody(player.getName())->SetLinearVelocity({0.0f, 0.0f});
            player.playAnimation(consts::MOVEMENT_PUNCH, consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else
        {
            player.playAnimation(consts::MOVEMENT_STOP, consts::DELAY_BETWEEN_ANIMATIONS);
            if (player.isAnimationStop())
            {
                physicsWorld->getBody(player.getName())->SetLinearVelocity({0.0f, 0.0f});
            }
        }
    }
}



