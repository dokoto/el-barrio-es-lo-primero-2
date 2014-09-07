#include "Sprite.hpp"
#include "errorsCodes.hpp"
#include "Names.hpp"


namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape, entity::TypeOfFixture typeOfFixture,
                              SDL_Color transparentColor, bool followWithCamera)
    {
        if (typeOfShape == entity::TypeOfShape::SHP_POLYGON && typeOfSprite == entity::TypeOfSprite::SPRT_CHARACTER )
        {
            foot.CreateObject(spriteName + name::FOOT_NAME, entity::TypeOfSprite::SPRT_NONE, entity::TypeOfShape::SHP_POLYGON, entity::TypeOfFixture::FIX_FOOT);
        }
                
        CreateObject(spriteName, typeOfSprite, typeOfShape, typeOfFixture);
        this->setTransparentColor(transparentColor);
        this->followWithCamera = followWithCamera;
    }        
    
}


