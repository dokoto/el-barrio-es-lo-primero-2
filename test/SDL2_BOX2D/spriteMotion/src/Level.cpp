#include "Level.hpp"
#include "Names.hpp"
#include "Measures.hpp"

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
            physicsWorld->getBody(player.getName())->SetLinearVelocity({NO_VELOCITY, -VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::DOWN]] )
        {
            physicsWorld->getBody(player.getName())->SetLinearVelocity({NO_VELOCITY, VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::LEFT]] )
        {
            player.setSide(Glob::Side::LEFT_SIDE);
            physicsWorld->getBody(player.getName())->SetLinearVelocity({-VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::RIGHT]] )
        {
            player.setSide(Glob::Side::RIGHT_SIDE);
            physicsWorld->getBody(player.getName())->SetLinearVelocity({VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::PUNCH]] )
        {
            physicsWorld->getBody(player.getName())->SetLinearVelocity({NO_VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_PUNCH, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else
        {
            player.playAnimation(name::MOVEMENT_STOP, measure::DELAY_BETWEEN_ANIMATIONS);
            if (player.isAnimationStop())
            {
                physicsWorld->getBody(player.getName())->SetLinearVelocity({NO_VELOCITY, NO_VELOCITY});
            }
        }
        
        b2Vec2 position = physicsWorld->getBody(player.getName())->GetPosition();
        auto it = physicsWorld->characterSortedByPosition.find(position.y);
        if (it != physicsWorld->characterSortedByPosition.end())
        {
            auto last = physicsWorld->characterSortedByPosition.rbegin()->second;
            position = last->GetPosition();
            position.y++;
        }
        
        physicsWorld->characterSortedByPosition.insert
        ( std::make_pair( position.y, physicsWorld->getBody(player.getName()) ) );
    }
    
    void Level::IA(void)
    {
        Character* tmpCharacter = nullptr;
        Object* obj = nullptr;
        
        auto itCharacters = physicsWorld->bodiesBySpriteType.equal_range(entity::TypeOfSprite::SPRT_CHARACTER);
        for (auto itElems = itCharacters.first; itElems != itCharacters.second; itElems++)
        {
            for (b2Fixture* fixtureElement = itElems->second->GetFixtureList(); fixtureElement; fixtureElement = fixtureElement->GetNext())
            {
                obj = static_cast<Object*>(fixtureElement->GetUserData());
                if (obj->whoAmI() == Glob::Classes::TEXTURE)
                {
                    tmpCharacter = static_cast<Character*>(fixtureElement->GetUserData());
                    if (tmpCharacter->getTypeOfFixture() == entity::FIX_ENEMY)
                    {
                        b2Vec2 position = itElems->second->GetPosition();
                        auto it = physicsWorld->characterSortedByPosition.find(position.y);
                        if (it != physicsWorld->characterSortedByPosition.end())
                        {
                            auto last = physicsWorld->characterSortedByPosition.rbegin()->second;
                            position = last->GetPosition();
                            position.y++;
                        }
                        physicsWorld->characterSortedByPosition.insert( std::make_pair( position.y, itElems->second ) );
                    }
                }
            }
        }
    }
}



