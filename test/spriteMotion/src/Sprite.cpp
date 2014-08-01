#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    Sprite::Sprite(const std::string& lname, Physics* world):
    name{lname},
    velocity{0, 0},
    position{0, 0},
    physicsWorld{world}
    {
        if (world == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics is mandatory to init the Sprite. Now is nullptr.");
            throw error::PHYSICS_MANDATORY;
        }
        
    }
    
    Sprite::~Sprite(void)
    {
        
    }
    
}
