#include "Character.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"


namespace barrio {
    using namespace std;
    
    Character::Character(const std::string& name, SDL_Renderer*& lrenderer):
    Sprite{name},
    renderer{lrenderer},
    currentAnimationFrame{0},
    delayFrameCount{0},
    currentAnimation{""}
    {        
    }
    
    Character::~Character()
    {
        
    }
    

    
    Animation Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        SDL_Rect currentClip = animations[animationName].at(currentAnimationFrame);
        b2Vec2 position = this->getPhysicsBody()->GetPosition();
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
        }
        currentAnimationFrame = (currentAnimationFrame == animations[animationName].size()) ? 0 : currentAnimationFrame;
        delayFrameCount++;
        return Animation {position, currentClip};

    }
    
    void Character::stopAnimation()
    {
        currentAnimation.clear();
        currentAnimationFrame = 0;
    }
    
    void Character::setVelocity(b2Vec2 velocity)
    {
        this->getPhysicsBody()->SetLinearVelocity(velocity);
    }
    
    void Character::loadSpriteSheetsJson(const std::string& spriteSheetsJsonPath)
    {
        Json::Reader jsonReader;
        Json::Value jsonRoot;
        ifstream jsonFile;
        
        jsonFile.open(spriteSheetsJsonPath.c_str(), ios::binary);
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
                        spriteCoords.push_back(rect);
                    }
                    
                    animations.insert(make_pair(it.key().asString(), spriteCoords));
                }
            }
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Error reading Json SpriteSheet file in : %s because:", spriteSheetsJsonPath.c_str(), strerror( errno ));
            throw error::READ_SPRITESHEETS_JSON_FAIL;
        }
        
    }
    
}