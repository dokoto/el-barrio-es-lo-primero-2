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
        Sprite(const std::string& lname);
        ~Sprite(void);
        
    private:
        std::string name;
        
    protected:
        Physics* physicsWorld;
        b2Body* body;
        
    public:
        b2Body* getPhysicsBody()
        {
            return body;
        }
        
        std::string getName() const { return this->name; }
        void setName(const std::string& name){ this->name = name; }
        
        const b2Vec2 getVelocity() const { return body->GetLinearVelocity(); }
        void setVelocity(const b2Vec2& velocity){ body->SetLinearVelocity(velocity); }
        
        const b2Vec2 getPosition() { return body->GetPosition(); }
        void setPosition(const b2Vec2& position){ body->GetPosition(); }
        
        float32 getPhysicsWidth() { return physicsWorld->convPixelsToCartesian(this->getWidth()); }
        float32 getPhysicsHeight() { return physicsWorld->convPixelsToCartesian(this->getHeight()); }
        
        void addToPhysicsWorld(Physics* world, const float32 physicsPosX, const float32 physicsPosY);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */
