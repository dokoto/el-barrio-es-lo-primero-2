#include "Furnitures.hpp"

#include <fstream>

#include "contrib/json.h"
#include "ErrorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Furnitures::CreateFurnitures(const std::string& groupName, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape, entity::TypeOfFixture typeOfFixture,
                                      SDL_Renderer*& renderer, SDL_Color transparentColor)
    {
        this->CreateSprite(groupName, typeOfSprite, typeOfShape, typeOfFixture, transparentColor);
        this->renderer = renderer;
    }
    
    void Furnitures::setSide(Glob::Side)
    {
    }
    
    bool Furnitures::getSide()const
    {
        return Glob::Side::RIGHT_SIDE;
    }
    
    SDL_Rect Furnitures::getFurnitureClip(const std::string& furnitureElemenName)
    {
        map<string, SDL_Rect>::iterator it;
        it = furnituresPixelDimensions.find(furnitureElemenName);
        if (it != furnituresPixelDimensions.end())
        {
            return furnituresPixelDimensions[furnitureElemenName];
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

