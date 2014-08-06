#ifndef __EL_BARRIO_ES_LO_PRIMERO__Sprite__
#define __EL_BARRIO_ES_LO_PRIMERO__Sprite__

#include <string>
#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Physics.hpp"
#include "Utils.hpp"

namespace barrio {
    
    
    class Sprite : public Texture
    {
    public:
        void CreateSprite(const std::string& name, Physics* world);
        Sprite(void) : physicsWorld(nullptr), body(nullptr) {}
        virtual ~Sprite(void)
        {
            printf("Destroy Physics Sprite %s...OK\n", name.c_str());
        }
        
    private:
        std::string name;
        
        Sprite(const Sprite&){}
        Sprite& operator=(const Sprite&);
        
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
        
        float32 getPhysicsFullTextureWidth() { return Utils::convWidthScreenToCartesian(this->getPixelWidth()); }
        float32 getPhysicsFullTextureHeight() { return Utils::convHeightScreenToCartesian(this->getPixelHeight()); }
        
        void addToPhysicsWorldAsPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight);
        void addToPhysicsWorldAsStaticPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */
