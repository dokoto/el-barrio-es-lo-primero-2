#ifndef __EL_BARRIO_ES_LO_PRIMERO__Physics__
#define __EL_BARRIO_ES_LO_PRIMERO__Physics__

#include <map>
#include <utility>
#include <string>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "CollisionListener.hpp"
#include "Size.hpp"
#include "Sprite.hpp"


namespace barrio {
    
    class Physics
    {
    public:        
        Physics(void) : world(nullptr) {}
        ~Physics(void);
        void CreateWorld(const b2Vec2 gravity, const Size<int>& screenSize);
        Physics(const Physics&& a);
        
        void addToWorld(const std::string& name, Sprite* sprite, const SDL_Point& screenPos, const Size<int>& screenSize,
                           const bool dynamicBody = true, const bool disableRotation = true);
        void setWorldBundaries(const int width, const int height);
        void createLine(const b2Vec2& pointA, const b2Vec2& pointB);
        
        bool bodyExist(const std::string& name);
        b2Body* getBody(const std::string& spriteNamme);
        
        void setHorizon(void);
        
        void Step(void)
        {
            world->Step(timeStep, this->velocityIterations, this->positionIterations);
        }
        
        b2World* getWorld(void) { return world; }
        
    public:
        CollisionListener collisionPool;
        std::map<std::string, b2Body*> bodiesByName;
        std::multimap<Sprite::TypeOfSprite, b2Body*> bodiesBySpriteType;
        std::multimap<Sprite::TypeOfShape, b2Body*> bodiesByShapeType;
        
    private:
        
        Physics(const Physics&){}
        Physics& operator=(const Physics&);
        b2Body* createPolygon(const std::string& name, Sprite* sprite, const SDL_Point& screenPos, const Size<int>& screenSize,
                           const bool dynamicBody = true, const bool disableRotation = true);
        
    private:
        b2Vec2 gravity;
        b2World* world;
        Size<float32> cartesianSize;        
        static constexpr float32 frequency = 30.0f;
        static constexpr int32 velocityIterations = 8;
        static constexpr int32 positionIterations = 3;
        static constexpr float32 timeStep = 1.0f / frequency;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Physics__) */
