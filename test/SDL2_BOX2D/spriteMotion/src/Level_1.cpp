#include "Level_1.hpp"
#include "Names.hpp"
#include "Flags.hpp"

namespace barrio
{
    using namespace std;
    
    void Level_1::loadLevelWorld(void)
    {
        /*
         * BACKGROUND
         */
        camera->loadBackGroundImage("img/backgorund_1679x600.png", renderer);
        
        /*
         * Players
         */
        playerA.CreateCharacter(name::PLAYER_ONE_NAME, entity::TypeOfSprite::SPRT_CHARACTER, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_CHARACTER, renderer);
        //playerA.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 15.0);
        playerA.loadAnimations("conf/spriteSheets/player1.json", "img/player1.png", 2.0, 2.0);
        playerA.setMovement(Sprite::Movement::UP, SDL_SCANCODE_UP);
        playerA.setMovement(Sprite::Movement::DOWN, SDL_SCANCODE_DOWN);
        playerA.setMovement(Sprite::Movement::LEFT, SDL_SCANCODE_LEFT);
        playerA.setMovement(Sprite::Movement::RIGHT, SDL_SCANCODE_RIGHT);
        playerA.setMovement(Sprite::Movement::PUNCH, SDL_SCANCODE_SPACE);
        physicsWorld->addToWorld("PlayerONE", &playerA, SDL_Point{800, 500}, playerA.getAnimationSize(name::MOVEMENT_STOP),
                                 flag::DYNAMIC_BODY, flag::DISABLE_ROTATION);
        
        playerB.CreateCharacter(name::PLAYER_TWO_NAME, entity::TypeOfSprite::SPRT_CHARACTER, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_CHARACTER, renderer);
        //playerB.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 5.0);
        playerB.loadAnimations("conf/spriteSheets/player2.json", "img/player2.png", 2.0, 2.0);
        playerB.setMovement(Sprite::Movement::UP, SDL_SCANCODE_W);
        playerB.setMovement(Sprite::Movement::DOWN, SDL_SCANCODE_S);
        playerB.setMovement(Sprite::Movement::LEFT, SDL_SCANCODE_A);
        playerB.setMovement(Sprite::Movement::RIGHT, SDL_SCANCODE_D);
        physicsWorld->addToWorld("PlayerTWO", &playerB, SDL_Point{900, 500}, playerB.getAnimationSize(name::MOVEMENT_STOP),
                                 flag::DYNAMIC_BODY, flag::DISABLE_ROTATION);
        
        /*
         * ENEMIES
         */
        unique_ptr<Character> enemy_buba;
        
        // ENEMY 1
        enemy_buba = unique_ptr<Character>(new Character());
        enemy_buba->CreateCharacter(name::ENEMY_BUBA, entity::TypeOfSprite::SPRT_CHARACTER, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_ENEMY,
                               renderer, SDL_Color{186, 254, 202, 0});
        enemy_buba->loadAnimations("conf/spriteSheets/enemy_1.json", "img/enemy_1.png", 2.0, 2.0);
        enemy_buba->setAIMode(Glob::AIMode::AI_PURSUIT);
        enemy_buba->setTarget(name::PLAYER_ONE_NAME);

        physicsWorld->addToWorld(name::ENEMY_BUBA, enemy_buba.get(), SDL_Point{60, 430}, enemy_buba->getAnimationSize(name::MOVEMENT_STOP),
                                                           flag::DYNAMIC_BODY, flag::DISABLE_ROTATION);
        
        enemiesGroup.insert(std::make_pair(name::ENEMY_BUBA, std::move(enemy_buba)));

        // ENEMY 2
        enemy_buba = unique_ptr<Character>(new Character());
        enemy_buba->CreateCharacter(name::ENEMY_BUBA_2, entity::TypeOfSprite::SPRT_CHARACTER, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_ENEMY,
                                    renderer, SDL_Color{186, 254, 202, 0});
        enemy_buba->loadAnimations("conf/spriteSheets/enemy_1.json", "img/enemy_1.png", 2.0, 2.0);
        enemy_buba->setAIMode(Glob::AIMode::AI_PURSUIT);
        enemy_buba->setTarget(name::PLAYER_ONE_NAME);
        
        physicsWorld->addToWorld(name::ENEMY_BUBA_2, enemy_buba.get(), SDL_Point{100, 490}, enemy_buba->getAnimationSize(name::MOVEMENT_STOP),
                                 flag::DYNAMIC_BODY, flag::DISABLE_ROTATION);
        
        enemiesGroup.insert(std::make_pair(name::ENEMY_BUBA_2, std::move(enemy_buba)));
 
        // ENEMY 3
        enemy_buba = unique_ptr<Character>(new Character());
        enemy_buba->CreateCharacter(name::ENEMY_BUBA_3, entity::TypeOfSprite::SPRT_CHARACTER, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_ENEMY,
                                    renderer, SDL_Color{186, 254, 202, 0});
        enemy_buba->loadAnimations("conf/spriteSheets/enemy_1.json", "img/enemy_1.png", 2.0, 2.0);
        enemy_buba->setAIMode(Glob::AIMode::AI_PURSUIT);
        enemy_buba->setTarget(name::PLAYER_ONE_NAME);
        
        physicsWorld->addToWorld(name::ENEMY_BUBA_3, enemy_buba.get(), SDL_Point{140, 500}, enemy_buba->getAnimationSize(name::MOVEMENT_STOP),
                                 flag::DYNAMIC_BODY, flag::DISABLE_ROTATION);
        
        enemiesGroup.insert(std::make_pair(name::ENEMY_BUBA_3, std::move(enemy_buba)));
        
        /*
         * FURNITURES
         */
        furnitures.CreateFurnitures("ObjectsGroup", entity::TypeOfSprite::SPRT_FURNITURE, entity::TypeOfShape::SHP_POLYGON,
                                    entity::TypeOfFixture::FIX_FURNITURE, renderer, SDL_Color{0, 255, 0, 0});
        furnitures.loadFurnitures("conf/spriteSheets/furniture_1.json", "img/furnitures_1.png", 0.3, 0.3);
        physicsWorld->addToWorld("objeto1", &furnitures, SDL_Point{500, 550}, furnitures.getFurnitureSize("objeto1"),
                                 flag::STATIC_BODY, flag::DISABLE_ROTATION);
        
        /*
         * TEXTS
         */
        texts->CreateText("ARIAL_12", "ttf/ArialNarrowRegular.ttf", 12);
        
        /*
         * WORLD BUNDARIES
         */
        worldBundaries.CreateObject(name::WORLD_BUNDARIES_NAME, nullptr, entity::SPRT_NONE, entity::SHP_CHAIN, entity::FIX_WORLD_BUDARIES);
        physicsWorld->setWorldBundaries(&worldBundaries, measure::WORLD_WIDTH_PX, measure::WORLD_HEIGHT_PX);
        
        /*
         * HORIZON
         */
        horizon.CreateObject(name::HORIZON_NAME, nullptr, entity::SPRT_NONE, entity::SHP_CHAIN, entity::FIX_HORIZON );
        physicsWorld->setHorizon(&horizon);
    }
    
    void Level_1::releaseClycleLiveTimeResources(void)
    {
        physicsWorld->characterSortedByPosition.clear();
    }
    
}

