#include "Level.hpp"
#include "Names.hpp"
#include "Measures.hpp"
#include "ErrorsCodes.hpp"
#include "Glob.hpp"
#include "Fixture.hpp"

namespace  barrio
{
    void Level::CreateLevel(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts)
    {
        this->renderer = renderer;
        this->physicsWorld = physicsWorld;
        this->camera = camera;
        this->texts = texts;
    }
    
    void Level::destroyEnemyGroup(void)
    {
        for (auto it = enemiesGroup.begin(); it != enemiesGroup.end(); it++)
        {
            if (it->second != nullptr)
            {
                delete it->second;
            }
        }
    }
    
    void Level::destroyElementsFromPhysicsWorld(void)
    {
        // Eliminar Furnitures
        // Eliminar Enemies
        // Eliminar Players
    }
    
    Level::~Level(void)
    {
        destroyEnemyGroup();
    }
    
    void Level::handleInputPlayer(Character& player)
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if (currentKeyStates[player.movements[Sprite::Movement::UP]] )
        {
            physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({NO_VELOCITY, -VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::DOWN]] )
        {
            physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({NO_VELOCITY, VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::LEFT]] )
        {
            player.setSide(Glob::Side::LEFT_SIDE);
            physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({-VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::RIGHT]] )
        {
            player.setSide(Glob::Side::RIGHT_SIDE);
            physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::Movement::PUNCH]] )
        {
            physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({NO_VELOCITY, NO_VELOCITY});
            player.playAnimation(name::MOVEMENT_PUNCH, measure::DELAY_BETWEEN_ANIMATIONS);
        }
        else
        {
            player.playAnimation(name::MOVEMENT_STOP, measure::DELAY_BETWEEN_ANIMATIONS);
            if (player.isAnimationStop())
            {
                physicsWorld->getBody(player.getBody()->getName())->SetLinearVelocity({NO_VELOCITY, NO_VELOCITY});
            }
        }
        
        // Se carga un mapa con la posicion vertical de cada jugador renderizar en funcion de la distacia
        b2Vec2 position = physicsWorld->getBody(player.getBody()->getName())->GetPosition();
        auto it = physicsWorld->characterSortedByPosition.find(position.y);
        if (it != physicsWorld->characterSortedByPosition.end())
        {
            auto last = physicsWorld->characterSortedByPosition.rbegin()->second;
            position = last->GetPosition();
            position.y++;
        }
        
        physicsWorld->characterSortedByPosition.insert
        ( std::make_pair( position.y, physicsWorld->getBody(player.getBody()->getName()) ) );
    }
    
    void Level::IA(void)
    {
     
        Character* enemy = nullptr;
        Object* obj = nullptr;
        bool twoPlayer = false;
        b2Vec2 playerONEPos, playerTWOPos, enemyPos;
        static constexpr int numOfAttacksByPlayer = 1;
        
        // Se analiza el numero de jugadores y se obtiene la posicion de cada uno
        auto playerONE = physicsWorld->bodiesByName.find(name::PLAYER_ONE_NAME);
        if (playerONE == physicsWorld->bodiesByName.end())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Player % not found", name::PLAYER_ONE_NAME);
            throw error::PLAYER_NOT_FOUND;
        }
        playerONEPos = playerONE->second->GetPosition();
        auto playerTWO = physicsWorld->bodiesByName.find(name::PLAYER_TWO_NAME);
        if (playerTWO != physicsWorld->bodiesByName.end())
        {
            twoPlayer = true;
            playerTWOPos = playerTWO->second->GetPosition();
        }
        
        auto intervalEnemies = physicsWorld->bodiesByFixtureType.equal_range(entity::TypeOfFixture::FIX_ENEMY);
        for (auto itEnemy = intervalEnemies.first; itEnemy != intervalEnemies.second; itEnemy++)
        {
            enemy = static_cast<Character*>(utls::Fixture::getCharcaterUserData(itEnemy->second));
            if (enemy != nullptr && enemy->getBody()->getTypeOfFixture() == entity::TypeOfFixture::FIX_ENEMY)
            {
                // Obtener posicion del enemigo
                enemyPos = itEnemy->second->GetPosition();
                if (enemy->getAIMode() == Glob::AIMode::AI_PURSUIT)
                {
                    
                }
                else if (enemy->getAIMode() == Glob::AIMode::AI_ATTACK)
                {
                    b2Body* bodyPlayer = (enemy->getTarget().compare(name::PLAYER_ONE_NAME) == 0) ? playerONE->second : playerTWO->second;
                    b2Vec2 positionPlayer = bodyPlayer->GetPosition();
                    if (positionPlayer.x > (abs(enemyPos.x) - 2) )
                    {
                        if (positionPlayer.x > enemyPos.x)
                            itEnemy->second->SetLinearVelocity(b2Vec2{1.2f, 0.0f});
                        else
                            itEnemy->second->SetLinearVelocity(b2Vec2{1.2f, 0.0f});
                        if (enemy->isAnimationStop())
                            enemy->playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
                    }
                    else
                    {
                        if (positionPlayer.y > (abs(enemyPos.y) - 0.3f) )
                        {
                            if (positionPlayer.y > enemyPos.y)
                                itEnemy->second->SetLinearVelocity(b2Vec2{0.0f, 1.2f});
                            else
                                itEnemy->second->SetLinearVelocity(b2Vec2{0.0f, -1.2f});
                            if (enemy->isAnimationStop())
                                enemy->playAnimation(name::MOVEMENT_WALKING, measure::DELAY_BETWEEN_ANIMATIONS);
                        }
                        else
                        {
                            // Punch
                            itEnemy->second->SetLinearVelocity(b2Vec2{0.0f, 0.0f});
                            if (enemy->isAnimationStop())
                                enemy->playAnimation(name::MOVEMENT_PUNCH, measure::DELAY_BETWEEN_ANIMATIONS);
                        }
                    }
                }
                
                // Se carga un mapa con la posicion vertical de cada enemigo para renderizar en funcion de la distacia
                auto it = physicsWorld->characterSortedByPosition.find(enemyPos.y);
                if (it != physicsWorld->characterSortedByPosition.end())
                {
                    auto last = physicsWorld->characterSortedByPosition.rbegin()->second;
                    enemyPos = last->GetPosition();
                    enemyPos.y++;
                }
                physicsWorld->characterSortedByPosition.insert( std::make_pair( enemyPos.y, itEnemy->second ) );
                
            }
            
        }
      
    }
}



