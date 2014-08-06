#include "Furnitures.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"
#include "Utils.hpp"

namespace barrio {
    
    using namespace std;
    
    void Furnitures::CreateFurnitures(const std::string& name, SDL_Renderer*& renderer, Physics* physicsWorld)
    {
        this->CreateSprite(name, physicsWorld);
        this->renderer = renderer;
    }
    
    void Furnitures::addToPhysicsWorld(void)
    {
        float32 cartesianWidth = 0.0f, cartesianHeight = 0.0f;
        float32 cartesianPosX = 0.0f, cartesianPosY = 0.0f;
        for(map<std::string, SDL_Rect>::iterator it = furnitures.begin(); it != furnitures.end(); it++)
        {
            cartesianWidth = Utils::convWidthScreenToCartesian(it->second.w);
            cartesianHeight = Utils::convHeightScreenToCartesian(it->second.h);
            cartesianPosX = Utils::convXScreenToCartesian(it->second.x);
            cartesianPosY = Utils::convYScreenToCartesian(it->second.y);
            
            addToPhysicsWorldAsStaticPolygon(it->first, cartesianPosX, cartesianPosY, cartesianWidth, cartesianHeight);

            cartesianWidth = 0.0f, cartesianHeight = 0.0f;
            cartesianPosX = 0.0f, cartesianPosY = 0.0f;
        }
    }
    
    Clip Furnitures::getFurnitureClip(const std::string& furnitureName)
    {
        map<string, SDL_Rect>::iterator it;
        it = furnitures.find(furnitureName);
        if (it != furnitures.end())
        {
            SDL_Rect rect = furnitures[furnitureName];
            b2Vec2 position = this->getPhysicsBody()->GetPosition();
            return Clip{position, rect};
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Furniture %s not found:", furnitureName.c_str());
            return Clip{};
        }
    }
    
    void Furnitures::loadJsonSheet(const std::string& jsonSheetPath, const double zoomX, const double zoomY)
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
                    
                    SDL_Rect rect = {(*it)["x"].asInt(), (*it)["y"].asInt(), (*it)["w"].asInt(), (*it)["h"].asInt()};
                    if (zoomX != 1 && zoomY != 1)
                    {
                        rect.x *= zoomX;
                        rect.y *= zoomY;
                        rect.w *= zoomX;
                        rect.h *= zoomY;
                    }
                    
                    furnitures.insert(make_pair(it.key().asString(), rect));
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

