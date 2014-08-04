#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& name, Physics* world)
    {
        this->name = name;
        if (world == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        this->physicsWorld = world;
    }
    
    void Sprite::addToPhysicsWorld(const float32 physicsPosX, const float32 physicsPosY)
    {
        if (physicsWorld == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        
        float32 width = this->getPhysicsWidth(), height = this->getPhysicsHeight();
        string name = this->getName();
        
        if (width == 0.0f && height == 0.0f)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Sprite dimensions are 0.0f, please load PNG and JSON datas first with Character->loadAnimations().");
            throw error::SPRITE_DIMENSIONS_NOT_FOUND;
        }
        
        physicsWorld->createPolygon(name, width, height, b2Vec2{physicsPosX, physicsPosY});
        body = physicsWorld->getBody(name);
    }
    
}
