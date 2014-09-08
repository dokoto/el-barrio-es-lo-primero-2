#ifndef __EL_BARRIO_ES_LO_PRIMERO__Object__
#define __EL_BARRIO_ES_LO_PRIMERO__Object__

#include <string>
#include "Glob.hpp"
#include "Entities.hpp"

namespace barrio
{    
    class Object
    {        
    private:
        std::string name;
        entity::TypeOfSprite typeOfSprite;
        entity::TypeOfShape typeOfShape;
        entity::TypeOfFixture typeOfFixture;
        
    private:
        Object(const Object&){}
        Object& operator=(const Object&);
        
    public:
        Object(const Object&& o): name(o.name), typeOfSprite(o.typeOfSprite), typeOfShape(o.typeOfShape), typeOfFixture(o.typeOfFixture) {}
        virtual ~Object(void) {}
        virtual Glob::Classes whoAmI(void) { return Glob::Classes::CLASS_OBJECT; }
        Object& operator=(const Object&& o)
        {
            typeOfSprite = o.typeOfSprite;
            typeOfShape = o.typeOfShape;
            typeOfFixture = o.typeOfFixture;
            
            return *this;
        }                
        
    public:
        
        Object(void): name(""), typeOfSprite(entity::TypeOfSprite::SPRT_NONE), typeOfShape(entity::TypeOfShape::SHP_NONE), typeOfFixture(entity::TypeOfFixture::FIX_NONE) {}
        void CreateObject(std::string name, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape, entity::TypeOfFixture typeOfFixture)
        {
            this->name = name;
            this->typeOfSprite = typeOfSprite;
            this->typeOfShape = typeOfShape;
            this->typeOfFixture = typeOfFixture;
        }
        
        std::string getName(void) const { return name; }
        entity::TypeOfSprite getTypeOfSprite(void) const { return typeOfSprite; }
        entity::TypeOfShape getTypeOfShape(void) const { return typeOfShape; }
        entity::TypeOfFixture getTypeOfFixture(void) const { return typeOfFixture; }
        virtual bool amObject(void) { return true; }
        
    };
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Object__) */

