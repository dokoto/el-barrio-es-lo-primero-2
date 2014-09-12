#ifndef __EL_BARRIO_ES_LO_PRIMERO__Level__
#define __EL_BARRIO_ES_LO_PRIMERO__Level__

#include <map>
#include <memory>

#include <SDL2/SDL.h>

#include "Sprite.hpp"
#include "Physics.hpp"
#include "Text.hpp"
#include "Camera.hpp"
#include "Character.hpp"

namespace barrio {
    
    class Level
    {
    public:
        Level(void) : renderer(nullptr), physicsWorld(nullptr), camera(nullptr), texts(nullptr) {}
        virtual ~Level(void);
        virtual void CreateLevel(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts);
        virtual void handleInputPlayer(Character& player);
        virtual void IA(void);
        virtual void loadLevelWorld(void) = 0;
        virtual void handleInput(void) = 0;
        virtual void releaseClycleLiveTimeResources(void) = 0;
        
    private:
        void destroyElementsFromPhysicsWorld(void);
        
    protected:
        bool AI_PURSUIT_MOV_1(const float32 vel, const b2Vec2& margin, const b2Vec2& playerPos, const b2Vec2& enemyPos,
                             Character* playerCharacter, Character* enemyCharacter, b2Body* playerPhysicsBody, b2Body* enemyPhysicsBody);
        
        bool AI_PURSUIT_MOV_2(const float32 vel, const b2Vec2& margin, const b2Vec2& playerPos, const b2Vec2& enemyPos,
                            Character* playerCharacter, Character* enemyCharacter, b2Body* playerPhysicsBody, b2Body* enemyPhysicsBody);
        
    protected:
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        Camera* camera;
        Text* texts;
        Object worldBundaries, horizon;
        Character playerA, playerB;
        std::map<std::string, std::unique_ptr<Character>> enemiesGroup;
    
    private:
        static constexpr float32 VELOCITY = 1.90f;
        static constexpr float32 NO_VELOCITY = 0.00f;
        
        
    };
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Level__) */
