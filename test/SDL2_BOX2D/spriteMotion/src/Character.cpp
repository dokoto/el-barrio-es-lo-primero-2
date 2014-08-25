#include "Character.hpp"
#include <fstream>
#include "contrib/json.h"
#include "errorsCodes.hpp"
#include "Utils.hpp"


namespace barrio {
    using namespace std;
    
    void Character::CreateCharacter(const std::string& name, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape, SDL_Renderer*& renderer, SDL_Color transparentColor)
    {
        this->CreateSprite(name, typeOfSprite, typeOfShape, transparentColor);
        this->renderer = renderer;
        this->currentAnimationFrame = 0;
        this->delayFrameCount = 0;
        this->currentAnimationName = "";
    }


    void Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        if (this->currentAnimationName.empty())
            this->currentAnimationName = animationName;
        
        //SDL_Rect clip = animations[this->currentAnimationName].at(currentAnimationFrame);
        
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
        }
        if (currentAnimationFrame == animations[this->currentAnimationName].size())
            stopAnimation();
        
        delayFrameCount++;
        //return clip;
    }
    
    void Character::setToFlip(bool flip)
    {
        Sprite::setToFlip(flip);
    }
    
    bool Character::getToFlip(void) const
    {
        return Sprite::getToFlip();
    }
    
    void Character::stopAnimation()
    {
        currentAnimationName.clear();
        currentAnimationFrame = 0;
        delayFrameCount = 0;
    }
        
    void Character::loadJsonSheet(const std::string& jsonSheetPath, const double zoomX, const double zoomY)
    {
        Json::Reader jsonReader;
        Json::Value jsonRoot;
        ifstream jsonFile;
        
        jsonFile.open(jsonSheetPath.c_str(), ios::binary);
        if (jsonFile.is_open())
        {
            if (jsonReader.parse(jsonFile, jsonRoot))
            {
                for(Json::Value::iterator it = jsonRoot.begin(); it != jsonRoot.end(); it++)
                {
                    vector<SDL_Rect> spriteCoords;
                    for(Json::Value::iterator ita = (*it).begin(); ita != (*it).end(); ita++)
                    {
                        SDL_Rect rect = {(*ita)["x"].asInt(), (*ita)["y"].asInt(), (*ita)["w"].asInt(), (*ita)["h"].asInt()};
                        if (zoomX != 1 && zoomY != 1)
                        {
                            rect.x *= zoomX;
                            rect.y *= zoomY;
                            rect.w *= zoomX;
                            rect.h *= zoomY;
                        }
                        spriteCoords.push_back(rect);
                    }
                    
                    animations.insert(make_pair(it.key().asString(), spriteCoords));
                }
            }
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Error reading Json SpriteSheet file in : %s because:", jsonSheetPath.c_str(), strerror( errno ));
            throw error::READ_SPRITESHEETS_JSON_FAIL;
        }
        
    }
    
}