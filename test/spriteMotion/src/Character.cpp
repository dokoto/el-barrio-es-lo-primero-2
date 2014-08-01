#include "Character.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"

namespace barrio {
    using namespace std;
    
    Character::Character(const std::string& name, SDL_Renderer*& lrenderer, Physics* world):
    Sprite{name, world},
    renderer{lrenderer},
    currentAnimationFrame{0},
    currentAnimation{""}
    {        
    }
    
    Character::~Character()
    {
        
    }
    
    void Character::addSpriteToWorld(const int x, const int y)
    {
        this->setPosition(SDL_Point{x, y});
        this->physicsWorld->addSpritePolygon(this->getName(), this->getWidth(), this->getHeight(),
                                             b2Vec2{this->physicsWorld->convIN_X(x), this->physicsWorld->convIN_Y(y)} );
        Texture::render(x, y, renderer);
    }
    
    void Character::playAnimation(const std::string& animationName)
    {
        //unsigned frame = static_cast<unsigned>(currentAnimationFrame) / static_cast<unsigned>(animations[animationName].size());
        SDL_Rect currentClip = animations[animationName].at(static_cast<unsigned>(currentAnimationFrame));
        b2Vec2 position = this->getPhysicsBody()->GetPosition();
        render(this->physicsWorld->convOUT_X(position.x), this->physicsWorld->convOUT_Y(position.y), renderer, &currentClip);
        currentAnimationFrame = (currentAnimationFrame == animations[animationName].size()) ? 0 : currentAnimationFrame +1;
    }
    
    void Character::stopAnimation()
    {
        currentAnimation.clear();
        currentAnimationFrame = 0;
    }
    
    void Character::setVelocity(SDL_Point velocity)
    {
        this->getPhysicsBody()->SetLinearVelocity(b2Vec2{this->physicsWorld->convIN_X(velocity.x), this->physicsWorld->convIN_Y(velocity.y)});
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