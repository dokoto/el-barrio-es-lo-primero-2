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
        enum direcction {UP, DOWN, LEFT, RIGHT, PUNCH, DIRECCTION_NONE};
        enum typeOfFixture {FIX_CHARACTER, FIX_ENEMY, FIX_FURNITURE, FIX_HORIZON, FIX_WORLD_BUDARIES, FIX_FOOT, FIX_TYPE_OF_FIXTURE_NONE};
        enum TypeOfShape {POLYGON, CIRCLE, TYPE_OF_SHAPE_NONE};
        enum TypeOfSprite {CHARACTER, ENEMY, FURNITURE, BACKGROUND, TYPE_OF_SPRITE_NONE};
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
        static std::string getFixtureName(b2Fixture* fixture);
        static Sprite::TypeOfSprite getFixtureTypeOfSprite(b2Fixture* fixture);
        static Sprite::TypeOfShape getFixtureTypeOfShape(b2Fixture* fixture);
        static Sprite::typeOfFixture getFixtureTypeOfFixture(b2Fixture* fixture);
        
    private:
        Sprite(const Sprite&){}
        Sprite& operator=(const Sprite&);
        TypeOfSprite typeOfSprite;
        TypeOfShape typeOfShape;
        
    public:
        
        int movements[5];
        std::string spriteName;
        std::string spriteFootName;
        bool followWithCamera;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Sprite__) */


