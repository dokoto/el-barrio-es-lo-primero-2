#include "Physics.hpp"
#include "errorsCodes.hpp"
#include <SDL2/SDL.h>

namespace barrio {

    using namespace std;
    
    Physics::Physics(const float gravityX, const float gravityY):
    world(nullptr)
    {
        gravity.x = gravityX;
        gravity.y = gravityY;
        world = new b2World(gravity);
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
    
    void Physics::addPolygon(Texture& body)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(static_cast<float>(body.posX), static_cast<float>(body.posY));
        b2Body* local_body = world->CreateBody(&bodyDef);
        b2PolygonShape box;
        box.SetAsBox(static_cast<float>(body.width), static_cast<float>(body.height));
        local_body->CreateFixture(&box, 0.0f);
        
        bodies.push_back(local_body);
    }
    
    
}