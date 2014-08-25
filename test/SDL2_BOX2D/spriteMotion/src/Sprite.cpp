#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape, SDL_Color transparentColor, bool followWithCamera)
    {
        this->spriteName = spriteName;
        this->followWithCamera = followWithCamera;
        this->typeOfSprite = typeOfSprite;
        this->typeOfShape = typeOfShape;
        setTransparentColor(transparentColor);
    }
                              
}
                              
                              
