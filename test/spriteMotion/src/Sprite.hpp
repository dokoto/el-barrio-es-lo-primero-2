#ifndef __EL_BARRIO_ES_LO_PRIMERO__Sprite__
#define __EL_BARRIO_ES_LO_PRIMERO__Sprite__

#include <string>
#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Physics.hpp"

namespace barrio {
    
    
    class Sprite : public Texture
    {
    public:
        Sprite(const std::string& lname, Physics* world);
        ~Sprite(void);
        
    private:
        std::string name;
        SDL_Point velocity;
        SDL_Point position;
        
    protected:
        Physics* physicsWorld;
        
    public:
        b2Body* getPhysicsBody()
        {
            return physicsWorld->getBody(this->getName());
        }
        
        std::string getName() const { return this->name; }
        void setName(const std::string& name){ this->name = name; }
        
        const SDL_Point getVelocity() const { return this->velocity; }
        void setVelocity(const SDL_Point& velocity){ this->velocity.x = velocity.x; this->velocity.y = velocity.y; }
        
        const SDL_Point getPosition() const { return this->position; }
        void setPosition(const SDL_Point& position){ this->position.x = position.x; this->position.y = position.y; }    
            
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */
