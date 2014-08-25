#ifndef __EL_BARRIO_ES_LO_PRIMERO__Sprite__
#define __EL_BARRIO_ES_LO_PRIMERO__Sprite__

#include <string>
#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Utils.hpp"

namespace barrio
{        
    class Sprite : public Texture
    {
    public:
        enum direcction {UP, DOWN, LEFT, RIGHT, PUNCH};
        enum TypeOfShape {POLYGON, CIRCLE};
        enum TypeOfSprite {CHARACTER, ENEMY, FURNITURE, BACKGROUND};
        void CreateSprite(const std::string& spriteName, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape, SDL_Color transparentColor, bool followWithCamera = false);
        Sprite(void) {}
        virtual ~Sprite(void)
        {
            printf("Destroy Physics Sprite %s...OK\n", spriteName.c_str());
        }
        
        TypeOfSprite getTypeOfSprite(void) const { return typeOfSprite; }
        TypeOfShape getTypeOfShape(void) const { return typeOfShape; }
        void setMovement(const direcction dir, const int key)
        {
            movements[dir] = key;
        }
        
    private:
        Sprite(const Sprite&){}
        Sprite& operator=(const Sprite&);
        TypeOfSprite typeOfSprite;
        TypeOfShape typeOfShape;
        
    public:
        
        int movements[5];
        std::string spriteName;
        bool followWithCamera;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */


