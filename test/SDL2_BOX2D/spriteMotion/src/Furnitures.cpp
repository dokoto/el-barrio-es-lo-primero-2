#include "Furnitures.hpp"

#include <fstream>

#include "contrib/json.h"
#include "errorsCodes.hpp"
#include "Utils.hpp"

namespace barrio {
    
    using namespace std;
    
    void Furnitures::CreateFurnitures(const std::string& FurnituresName, SDL_Renderer*& renderer, Physics* physicsWorld, SDL_Color transparentColor)
    {
        this->CreateSprite(FurnituresName, transparentColor, physicsWorld);
        this->renderer = renderer;
    }
    
    void Furnitures::addToPhysicsWorld(const std::string& furnitureElemenName, const float32 cartesianPosX, const float32 cartesianPosY)
    {
        float32 cartesianWidth = 0.0f, cartesianHeight = 0.0f;
        map<string, SDL_Rect>::iterator it;
        it = furnituresPixelDimensions.find(furnitureElemenName);
        if (it != furnituresPixelDimensions.end())
        {
            cartesianWidth = Utils::convWidthScreenToCartesian(it->second.w);
            cartesianHeight = Utils::convHeightScreenToCartesian(it->second.h);
            addToPhysicsWorldAsStaticPolygon(it->first, cartesianPosX, cartesianPosY, cartesianWidth, cartesianHeight);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Furniture %s not found:", furnitureElemenName.c_str());
            throw error::FURNITURE_NOT_FOUND;
        }        
    }
    
    Clip Furnitures::getFurnitureClip(const std::string& furnitureElemenName)
    {
        map<string, SDL_Rect>::iterator it;
        it = furnituresPixelDimensions.find(furnitureElemenName);
        if (it != furnituresPixelDimensions.end())
        {
            SDL_Rect rect = furnituresPixelDimensions[furnitureElemenName];
            b2Vec2 position = getPhysicsPosition(furnitureElemenName);
            return Clip{position, rect};
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Furniture %s not found:", furnitureElemenName.c_str());
            throw error::READ_SPRITESHEETS_JSON_FAIL;
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
                    SDL_Rect rect;
                    rect = {(*it)["x"].asInt(), (*it)["y"].asInt(), (*it)["w"].asInt(), (*it)["h"].asInt()};
                    
                    if (zoomX != 1 && zoomY != 1)
                    {
                        rect.x *= zoomX;
                        rect.y *= zoomY;
                        rect.w *= zoomX;
                        rect.h *= zoomY;
                    }
                    
                    furnituresPixelDimensions.insert(make_pair(it.key().asString(), rect));
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

