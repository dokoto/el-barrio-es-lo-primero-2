#ifndef __EL_BARRIO_ES_LO_PRIMERO__Object__
#define __EL_BARRIO_ES_LO_PRIMERO__Object__

#include <string>
#include "Constants.hpp"

namespace barrio
{    
    class Object
    {
    public:
        
        enum TypeOfSprite {SPRT_CHARACTER, SPRT_ENEMY, SPRT_FURNITURE, SPRT_BACKGROUND, SPRT_NONE};
        enum TypeOfShape {SHP_POLYGON, SHP_CIRCLE, SHP_CHAIN, SHP_NONE};
        enum TypeOfFixture {FIX_CHARACTER, FIX_ENEMY, FIX_FURNITURE, FIX_FOOT, FIX_HORIZON, FIX_WORLD_BUDARIES, FIX_NONE};
        
        
    private:
        std::string name;
        TypeOfSprite typeOfSprite;
        TypeOfShape typeOfShape;
        TypeOfFixture typeOfFixture;
        
    private:
        Object(const Object&){}
        Object& operator=(const Object&);
        
    public:
        Object(const Object&& o): name(o.name), typeOfSprite(o.typeOfSprite), typeOfShape(o.typeOfShape), typeOfFixture(o.typeOfFixture) {}
        virtual ~Object(void) {}
        virtual consts::CLASSES whoAmI(void) { return consts::CLASSES::OBJECT; }
        Object& operator=(const Object&& o)
        {
            typeOfSprite = o.typeOfSprite;
            typeOfShape = o.typeOfShape;
            typeOfFixture = o.typeOfFixture;
            
            return *this;
        }
        
    public:
        
        Object(void): name(""), typeOfSprite(TypeOfSprite::SPRT_NONE), typeOfShape(TypeOfShape::SHP_NONE), typeOfFixture(TypeOfFixture::FIX_NONE) {}
        void CreateObject(std::string name, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape, TypeOfFixture typeOfFixture)
        {
            this->name = name;
            this->typeOfSprite = typeOfSprite;
            this->typeOfShape = typeOfShape;
            this->typeOfFixture = typeOfFixture;
        }
        
        std::string getName(void) const { return name; }
        TypeOfSprite getTypeOfSprite(void) const { return typeOfSprite; }
        TypeOfShape getTypeOfShape(void) const { return typeOfShape; }
        TypeOfFixture getTypeOfFixture(void) const { return typeOfFixture; }
        virtual bool amObject(void) { return true; }
        
    };
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Object__) */

