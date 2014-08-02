#include "Physics.hpp"
#include "errorsCodes.hpp"

namespace barrio {

    using namespace std;
    
    Physics::Physics(const b2Vec2 gravity, const int width, const int height):
    world(nullptr),
    middle_width(width/2),
    middle_height(height/2)
    {
        world = new b2World{gravity};
        if (world != nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE,
                           "Physics World initialization with gravity[%f/%f]...OK", gravity.x, gravity.y);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics World initialization has failed.");
            throw error::PHYSICS_INIT_FAIL;
        }
        
    }
    
    Physics::~Physics(void)
    {
        //Destroy physics
        if (world == nullptr)
        {
            delete world;
            world = nullptr;
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Destroy Physics World...OK");
        }
    }
    
    void Physics::addSpritePolygon(const std::string& spriteName, const float spriteWidth, const float spriteHeight, const b2Vec2& spritePosition)
    {
        map<string, b2Body*>::iterator it;
        it = bodies.find(spriteName);
        if (it != bodies.end())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Duplicate Physics body name", "llklk");
            throw error::PHYSICS_BODY_NAME_DUPLICATE;
        }
        b2BodyDef bodyDef;
        bodyDef.position.Set(spritePosition.x, spritePosition.y);
        b2Body* body = world->CreateBody(&bodyDef);
        b2PolygonShape box;
        box.SetAsBox(spriteWidth, spriteHeight);
        body->CreateFixture(&box, 0.0f);
        
        bodies.insert(make_pair(spriteName, body));
    }
    
    b2Body* Physics::getBody(const std::string& spriteName)
    {        
        map<string, b2Body*>::iterator it;
        it = bodies.find(spriteName);
        if (it == bodies.end())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No Physics body name: %s found", "llklk");
            throw error::PHYSICS_BODY_NAME_NOT_FOUND;
        }
        else
            return it->second;
        
        return nullptr;
        
    }        
}

