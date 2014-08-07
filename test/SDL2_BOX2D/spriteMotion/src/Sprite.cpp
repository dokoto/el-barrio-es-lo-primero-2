#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, SDL_Color transparentColor, Physics* world)
    {
        this->spriteName = spriteName;
        setTransparentColor(transparentColor);
        if (world == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        this->physicsWorld = world;
    }
    
    void Sprite::addToPhysicsWorldAsPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight)
    {
        if (physicsWorld == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        
        if (cartesianWidth == 0.0f && cartesianHeight == 0.0f)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Sprite dimensions are 0.0f, please load PNG and JSON datas first with Character->loadAnimations().");
            throw error::SPRITE_DIMENSIONS_NOT_FOUND;
        }
        
        physicsWorld->createPolygon(name, cartesianWidth, cartesianHeight, b2Vec2{cartesianPosX, cartesianPosY});
    }
    
    void Sprite::addToPhysicsWorldAsStaticPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight)
    {
        if (physicsWorld == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
                
        if (cartesianWidth == 0.0f && cartesianHeight == 0.0f)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Sprite dimensions are 0.0f, please load PNG and JSON datas first with Character->loadAnimations().");
            throw error::SPRITE_DIMENSIONS_NOT_FOUND;
        }
        
        physicsWorld->createStaticPolygon(name, cartesianWidth, cartesianHeight, b2Vec2{cartesianPosX, cartesianPosY});
    }
    
}
