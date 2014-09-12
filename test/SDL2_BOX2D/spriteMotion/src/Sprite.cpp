#include "Sprite.hpp"
#include "errorsCodes.hpp"
#include "Names.hpp"


namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape, entity::TypeOfFixture typeOfFixture,
                              SDL_Color transparentColor, bool followWithCamera)
    {
        if (typeOfShape == entity::TypeOfShape::SHP_POLYGON && typeOfSprite == entity::TypeOfSprite::SPRT_CHARACTER)
        {
            if (typeOfFixture == entity::FIX_CHARACTER)
                foot.CreateObject(spriteName + name::FOOT_NAME, this, entity::SPRT_NONE, entity::SHP_POLYGON, entity::FIX_CHARACTER_FOOT);
            else if (typeOfFixture == entity::FIX_ENEMY)
                foot.CreateObject(spriteName + name::FOOT_NAME, this, entity::SPRT_NONE, entity::SHP_POLYGON, entity::FIX_CHARACTER_FOOT);
            else
                foot.CreateObject(name::NOTHING, nullptr, entity::SPRT_NONE, entity::SHP_NONE, entity::FIX_NONE);
        }
                
        body.CreateObject(spriteName, this, typeOfSprite, typeOfShape, typeOfFixture);
        this->setTransparentColor(transparentColor);
        this->followWithCamera = followWithCamera;
        this->cartesianSize = {0.0f, 0.0f};
    }        
    
}


