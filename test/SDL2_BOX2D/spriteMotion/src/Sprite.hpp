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
        
        SDL_Point getScreenPosition(const std::string& bodyName);
        std::string getSpriteName() const { return this->spriteName; }
        void setSpriteName(const std::string& spriteName){ this->spriteName = spriteName; }        
        void addPolygonToPhysics(const std::string& name, const SDL_Point& screenPos, const Size<int>& screenSize, const bool dynamicBody = true);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */
