#ifndef __EL_BARRIO_ES_LO_PRIMERO__Sprite__
#define __EL_BARRIO_ES_LO_PRIMERO__Sprite__

#include <string>
#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Conv.hpp"
#include "Object.hpp"

namespace barrio
{        
    class Sprite : public Texture, public Object
    {
    public:
        enum Movement {UP, DOWN, LEFT, RIGHT, PUNCH, DIRECCTION_NONE};
        void CreateSprite(const std::string& spriteName, Object::TypeOfSprite typeOfSprite, Object::TypeOfShape typeOfShape,
                          Object::TypeOfFixture typeOfFixture, SDL_Color transparentColor, bool followWithCamera = false);
        Sprite(void) {}
        virtual ~Sprite(void)
        {
            printf("Destroy Physics Sprite %s...OK\n", getName().c_str());
        }
        
        void setMovement(const Movement dir, const int key)
        {
            movements[dir] = key;
        }
        Object* getFoot(void) { return &foot; }                        
        
    private:
        Sprite(const Sprite&){}
        Sprite& operator=(const Sprite&);
        
    public:
        Object foot;
        int movements[5];
        bool followWithCamera;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */


