#include "Character.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"
#include "Utils.hpp"


namespace barrio {
    using namespace std;
    
    void Character::CreateCharacter(const std::string& name, SDL_Renderer*& renderer, Physics* physicsWorld)
    {
        this->CreateSprite(name, physicsWorld);
        this->renderer = renderer;
        this->currentAnimationFrame = 0;
        this->delayFrameCount = 0;
        this->currentAnimation = "";
    }
    
    Clip Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        if (currentAnimation != animationName)
        {
            stopAnimation();
        }
        this->currentAnimation = animationName;
        SDL_Rect currentClip = animations[animationName].at(currentAnimationFrame);
        b2Vec2 position = this->getPhysicsBody()->GetPosition();
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
        }
        currentAnimationFrame = (currentAnimationFrame == animations[animationName].size()) ? 0 : currentAnimationFrame;
        delayFrameCount++;
        return Clip {position, currentClip};

    }
    
    void Character::stopAnimation()
    {
        currentAnimation.clear();
        currentAnimationFrame = 0;
        delayFrameCount = 0;
    }
    
    void Character::setVelocity(b2Vec2 velocity)
    {
        this->getPhysicsBody()->SetLinearVelocity(velocity);
    }
    
    void Character::addToPhysicsWorld(const float32 cartesianPosX, const float32 cartesianPosY)
    {
        float32 cartesianWidth = Utils::convWidthScreenToCartesian(animations.begin()->second.at(0).w);
        float32 cartesianHeight = Utils::convHeightScreenToCartesian(animations.begin()->second.at(0).h);
        addToPhysicsWorldAsPolygon(getName(), cartesianPosX, cartesianPosY, cartesianWidth, cartesianHeight);
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