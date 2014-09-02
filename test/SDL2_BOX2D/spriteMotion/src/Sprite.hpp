#ifndef __EL_BARRIO_ES_LO_PRIMERO__Sprite__
#define __EL_BARRIO_ES_LO_PRIMERO__Sprite__

#include <string>
#include <SDL2/SDL.h>

#include "Texture.hpp"
#include "Utils.hpp"
#include "Object.hpp"

namespace barrio
{        
    class Sprite : public Texture, public Object
    {
    public:
        enum direcction {UP, DOWN, LEFT, RIGHT, PUNCH, DIRECCTION_NONE};
        void CreateSprite(const std::string& spriteName, Object::TypeOfSprite typeOfSprite, Object::TypeOfShape typeOfShape,
                          Object::TypeOfFixture typeOfFixture, SDL_Color transparentColor, bool followWithCamera = false);
        Sprite(void) {}
        virtual ~Sprite(void)
        {
            printf("Destroy Physics Sprite %s...OK\n", getName().c_str());
        }
        
        void setMovement(const direcction dir, const int key)
        {
            movements[dir] = key;
        }
        Object* getFoot(void) { return &foot; }
        
        static std::string getFixtureName(b2Fixture* fixture);
        static Object::TypeOfSprite getFixtureTypeOfSprite(b2Fixture* fixture);
        static Object::TypeOfShape getFixtureTypeOfShape(b2Fixture* fixture);
        static Object::TypeOfFixture getFixtureTypeOfFixture(b2Fixture* fixture);
        
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


