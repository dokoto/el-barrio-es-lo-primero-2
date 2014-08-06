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
    
    void Furnitures::addToPhysicsWorld(const std::string& furnitureName, const float32 cartesianPosX, const float32 cartesianPosY)
    {
        float32 cartesianWidth = 0.0f, cartesianHeight = 0.0f;
        map<string, furnituresBodies>::iterator it;
        it = furnitures.find(furnitureName);
        if (it != furnitures.end())
        {
            cartesianWidth = Utils::convWidthScreenToCartesian(it->second.clip.w);
            cartesianHeight = Utils::convHeightScreenToCartesian(it->second.clip.h);
            addToPhysicsWorldAsStaticPolygon(it->first, cartesianPosX, cartesianPosY, cartesianWidth, cartesianHeight);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Furniture %s not found:", furnitureName.c_str());
            throw error::FURNITURE_NOT_FOUND;
        }        
    }
    
    Clip Furnitures::getFurnitureClip(const std::string& furnitureName)
    {
        map<string, furnituresBodies>::iterator it;
        it = furnitures.find(furnitureName);
        if (it != furnitures.end())
        {
            furnituresBodies rect = furnitures[furnitureName];
            b2Vec2 position = rect.body->GetPosition();
            return Clip{position, rect.clip};
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Furniture %s not found:", furnitureName.c_str());
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
                    furnituresBodies rect;
                    rect.clip = {(*it)["x"].asInt(), (*it)["y"].asInt(), (*it)["w"].asInt(), (*it)["h"].asInt()};
                    rect.body = nullptr;
                    if (zoomX != 1 && zoomY != 1)
                    {
                        rect.clip.x *= zoomX;
                        rect.clip.y *= zoomY;
                        rect.clip.w *= zoomX;
                        rect.clip.h *= zoomY;
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

