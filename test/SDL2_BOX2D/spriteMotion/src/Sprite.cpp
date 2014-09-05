#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, Object::TypeOfSprite typeOfSprite, Object::TypeOfShape typeOfShape, Object::TypeOfFixture typeOfFixture,
                              SDL_Color transparentColor, bool followWithCamera)
    {
        if (typeOfShape == TypeOfShape::SHP_POLYGON && ( typeOfSprite == TypeOfSprite::SPRT_CHARACTER || typeOfSprite == TypeOfSprite::SPRT_ENEMY ) )
        {
            foot.CreateObject(spriteName + consts::FOOT_NAME, TypeOfSprite::SPRT_NONE, TypeOfShape::SHP_POLYGON, TypeOfFixture::FIX_FOOT);
        }
                
        CreateObject(spriteName, typeOfSprite, typeOfShape, typeOfFixture);
        this->setTransparentColor(transparentColor);
        this->followWithCamera = followWithCamera;
    }        
    
}


