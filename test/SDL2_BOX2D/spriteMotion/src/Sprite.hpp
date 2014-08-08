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
        void CreateSprite(const std::string& spriteName, SDL_Color transparentColor, Physics* world);
        Sprite(void) : physicsWorld(nullptr) {}
        virtual ~Sprite(void)
        {
            printf("Destroy Physics Sprite %s...OK\n", spriteName.c_str());
        }
        
    private:
        std::string spriteName;        
        
        Sprite(const Sprite&){}
        Sprite& operator=(const Sprite&);
        
    protected:
        Physics* physicsWorld;
        
    public:
                
        inline b2Vec2 getPhysicsPosition (const std::string& physicsBodyName) const
        {
            return physicsWorld->getBody(physicsBodyName)->GetPosition();
        }
        
        inline b2Body* getPhysicsBody (const std::string& physicsBodyName) const
        {
            return physicsWorld->getBody(physicsBodyName);
        }
        
        std::string getSpriteName() const { return this->spriteName; }
        void setSpriteName(const std::string& spriteName){ this->spriteName = spriteName; }
                        
        inline float32 getPhysicsFullTextureWidth()
        {
            return Utils::convWidthScreenToCartesian(this->getPixelWidth());
        }
        
        inline float32 getPhysicsFullTextureHeight()
        {
            return Utils::convHeightScreenToCartesian(this->getPixelHeight());
        }
        
        void addToPhysicsWorldAsPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight);
        
        void addToPhysicsWorldAsStaticPolygon(const std::string& name, const float32 cartesianPosX, const float32 cartesianPosY, const float32 cartesianWidth, const float32 cartesianHeight);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */
