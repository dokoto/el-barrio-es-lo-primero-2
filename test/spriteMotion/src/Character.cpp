#include "Character.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"

namespace barrio {
    using namespace std;
    
    Character::Character(SDL_Renderer*& lrenderer):
        renderer(lrenderer),
        currentAnimationFrame(-1),
        currentAnimation("")
    {
        
    }
    
    Character::~Character()
    {
        
    }
    
    void Character::addSpriteToWorld(int x, int y)
    {
        Texture::render(x, y, renderer);
    }
    
    void Character::playAnimation(const std::string& animationName)
    {
        SDL_Rect currentClip = animations[animationName].at(currentAnimationFrame/animations[animationName].size());
        //Texture::render(<#const int x#>, <#const int y#>, renderer);
    }
    
    void Character::stopAnimation()
    {
        currentAnimation.clear();
        currentAnimationFrame = -1;
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
                    
                    animations.insert(pair<std::string, vector<SDL_Rect>>(it.key().toStyledString(), spriteCoords));
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