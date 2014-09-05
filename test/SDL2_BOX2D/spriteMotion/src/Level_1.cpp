#include "Level_1.hpp"

namespace barrio
{        
    void Level_1::loadLevelWorld(void)
    {
        camera->loadBackGroundImage("img/backgorund_1679x600.png", renderer);
        
        playerA.CreateCharacter("PlayerONE", Sprite::TypeOfSprite::SPRT_CHARACTER, Sprite::TypeOfShape::SHP_POLYGON, Sprite::TypeOfFixture::FIX_CHARACTER, renderer);
        //playerA.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 15.0);
        playerA.loadAnimations("conf/spriteSheets/player1.json", "img/player1.png", 2.0, 2.0);
        playerA.setMovement(Sprite::Movement::UP, SDL_SCANCODE_UP);
        playerA.setMovement(Sprite::Movement::DOWN, SDL_SCANCODE_DOWN);
        playerA.setMovement(Sprite::Movement::LEFT, SDL_SCANCODE_LEFT);
        playerA.setMovement(Sprite::Movement::RIGHT, SDL_SCANCODE_RIGHT);
        playerA.setMovement(Sprite::Movement::PUNCH, SDL_SCANCODE_SPACE);
        physicsWorld->addToWorld("PlayerONE", &playerA, SDL_Point{600, 550}, playerA.getAnimationSize(consts::MOVEMENT_STOP),
                                 consts::DYNAMIC_BODY, consts::DISABLE_ROTATION);
        
        playerB.CreateCharacter("PlayerTWO", Sprite::TypeOfSprite::SPRT_CHARACTER, Sprite::TypeOfShape::SHP_POLYGON, Sprite::TypeOfFixture::FIX_CHARACTER, renderer);
        //playerB.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 5.0);
        playerB.loadAnimations("conf/spriteSheets/player2.json", "img/player2.png", 2.0, 2.0);
        playerB.setMovement(Sprite::Movement::UP, SDL_SCANCODE_W);
        playerB.setMovement(Sprite::Movement::DOWN, SDL_SCANCODE_S);
        playerB.setMovement(Sprite::Movement::LEFT, SDL_SCANCODE_A);
        playerB.setMovement(Sprite::Movement::RIGHT, SDL_SCANCODE_D);
        physicsWorld->addToWorld("PlayerTWO", &playerB, SDL_Point{700, 580}, playerB.getAnimationSize(consts::MOVEMENT_STOP),
                                 consts::DYNAMIC_BODY, consts::DISABLE_ROTATION);
        
        furnitures.CreateFurnitures("ObjectsGroup", Sprite::TypeOfSprite::SPRT_FURNITURE, Sprite::TypeOfShape::SHP_POLYGON,
                                    Sprite::TypeOfFixture::FIX_FURNITURE, renderer, SDL_Color{0, 255, 0, 0});
        furnitures.loadFurnitures("conf/spriteSheets/furniture_1.json", "img/furnitures_1.png", 1.0, 1.0);
        physicsWorld->addToWorld("objeto1", &furnitures, SDL_Point{10, 10}, furnitures.getFurnitureSize("objeto1"),
                                 consts::STATIC_BODY, consts::DISABLE_ROTATION);
        
        
        texts->CreateText("ARIAL_12", "ttf/ArialNarrowRegular.ttf", 12);
        
        physicsWorld->setHorizon();
    }
    
    void Level_1::releaseClycleLiveTimeResources(void)
    {
        physicsWorld->collisionPool.clearCollisionObjectList();
    }
    
}

