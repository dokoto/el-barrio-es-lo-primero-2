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
    
    
    void Character::temp(void)
    {
        b2Body* tmp = physicsWorld->getWorld()->GetBodyList();
        b2Vec2 points[4];
        while(tmp)
        {
            for(int i=0;i<4;i++)
            {
                points[i]=((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
                Utils::rotateTranslate(points[i],tmp->GetWorldCenter(),tmp->GetAngle());
            }
//            printf("[%f, %f][%f, %f][%f, %f][%f, %f]\n", points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, points[3].x, points[3].y );
            tmp=tmp->GetNext();
        }
    }

    Clip Character::playAnimation(const std::string& animationName, const size_t delayInFrames)
    {
        if (this->currentAnimationName.empty())
            this->currentAnimationName = animationName;
        
        SDL_Rect originCLip = animations[this->currentAnimationName].at(currentAnimationFrame);

        SDL_Rect destinationClip;
        destinationClip.w = originCLip.w;
        destinationClip.h = originCLip.h;
        SDL_Point pp = getScreenPosition(this->getSpriteName());
        destinationClip.x = pp.x;
        destinationClip.y = pp.y;
        float32 angle = getPhysicsBody(getSpriteName())->GetAngle();
        
        if (delayFrameCount == delayInFrames)
        {
            delayFrameCount = 0;
            currentAnimationFrame++;
        }
        if (currentAnimationFrame == animations[this->currentAnimationName].size())
            stopAnimation();
        
        delayFrameCount++;
        return Clip {getSpriteName(), originCLip, destinationClip, angle};
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
    
    
    void Character::addToPhysicsWorld(const SDL_Point& screenPos)
    {
        physicsWorld->createPolygon(getSpriteName(), screenPos, Size<int> { animations["stop"].at(0).w, animations["stop"].at(0).h }, DYNAMIC_BODY);
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