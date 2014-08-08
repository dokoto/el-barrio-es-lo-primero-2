#include "Character.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"
#include "Utils.hpp"


namespace barrio {
    using namespace std;
    
    void Character::CreateCharacter(const std::string& name, SDL_Renderer*& renderer, Physics* physicsWorld, SDL_Color transparentColor)
    {
        this->CreateSprite(name, transparentColor, physicsWorld);
        this->renderer = renderer;
        this->currentAnimationFrame = 0;
        this->delayFrameCount = 0;
        this->currentAnimationName = "";
    }
    
    Clip Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        if (this->currentAnimationName.empty())
            this->currentAnimationName = animationName;
        
        SDL_Rect currentClip = animations[this->currentAnimationName].at(currentAnimationFrame);
        b2Vec2 position = getPhysicsBody(getSpriteName())->GetPosition();
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
        }
        if (currentAnimationFrame == animations[this->currentAnimationName].size())
            stopAnimation();
        
        delayFrameCount++;
        return Clip {position, currentClip};
    }
    /*
    Clip Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        if (this->currentAnimationName != animationName)
           stopAnimation();
        
        this->currentAnimationName = animationName;        
        SDL_Rect currentClip = animations[this->currentAnimationName].at(currentAnimationFrame);
        b2Vec2 position = getPhysicsBody(getSpriteName())->GetPosition();
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
            if (currentAnimationName != "stop")
                printf("[%d] [%d,%d] currentAnimationName: %s\n", currentAnimationFrame, currentClip.x, currentClip.y, this->currentAnimationName.c_str());
        }
        
        currentAnimationFrame = (currentAnimationFrame == animations[this->currentAnimationName].size()) ? 0 : currentAnimationFrame;
        delayFrameCount++;
        
        
        return Clip {position, currentClip};
    }
     */
    
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
    
    
    void Character::addToPhysicsWorld(const float32 cartesianPosX, const float32 cartesianPosY)
    {
        float32 cartesianWidth = Utils::convWidthScreenToCartesian(animations.begin()->second.at(0).w);
        float32 cartesianHeight = Utils::convHeightScreenToCartesian(animations.begin()->second.at(0).h);
        addToPhysicsWorldAsPolygon(getSpriteName(), cartesianPosX, cartesianPosY, cartesianWidth, cartesianHeight);
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