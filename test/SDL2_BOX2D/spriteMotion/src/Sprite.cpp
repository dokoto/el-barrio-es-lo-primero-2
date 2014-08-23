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
    
    void Sprite::addPolygonToPhysics(const std::string& name, const SDL_Point& screenPos, const Size<int>& screenSize, const bool dynamicBody)
    {
        if (physicsWorld == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        
        if (screenSize.w == 0 && screenSize.h == 0)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Sprite dimensions are 0.0f, please load PNG and JSON datas first with Character->loadAnimations().");
            throw error::SPRITE_DIMENSIONS_NOT_FOUND;
        }
        
        physicsWorld->createPolygon(name, screenPos, screenSize, dynamicBody);
    }

    SDL_Point Sprite::getScreenPosition(const std::string& bodyName)
    {        
        b2Vec2 point = ((b2PolygonShape*)getPhysicsBody(bodyName)->GetFixtureList()->GetShape())->GetVertex(0);
        Utils::rotateTranslate(point, getPhysicsBody(bodyName)->GetWorldCenter(), getPhysicsBody(bodyName)->GetAngle());
        
        return Utils::convCartesianPosToScreennPos(point);
    }
}
