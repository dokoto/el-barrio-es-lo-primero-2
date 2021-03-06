#ifndef __EL_BARRIO_ES_LO_PRIMERO__Staff__
#define __EL_BARRIO_ES_LO_PRIMERO__Staff__

#include <string>
#include <map>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include "Sprite.hpp"

namespace barrio {
    
    class Furnitures : public Sprite
    {
    public:
        void CreateFurnitures(const std::string& groupName, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape, entity::TypeOfFixture typeOfFixture, SDL_Renderer*& renderer, SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0});
        Furnitures(): renderer(nullptr) {}
        ~Furnitures() {}
        
        void loadFurnitures(const std::string& jsonSheetPath, const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadJsonSheet(jsonSheetPath, zoomX, zoomY);
            loadPngSheet(pngSheetPath, zoomX, zoomY);
        }
        
        SDL_Rect getFurnitureClip(const std::string& furnitureElemenName);
        std::map<std::string, SDL_Rect> getAllFurnitures(void)
        {
            return furnituresPixelDimensions;
        }
        
        Size<int> getFurnitureSize( const std::string& furnitureElemenName)
        {
            SDL_Rect r = getFurnitureClip(furnitureElemenName);
            return Size<int> {r.w, r.h};
        }
        
        Object* getBody(const std::string& name)
        {
            auto it = furnituresBodyObject.find(name);
            if (it != furnituresBodyObject.end())
                return it->second.get();
            else
                return nullptr;
        }
        
        void setSide(Glob::Side side);
        bool getSide(void) const;
        
    private:
        
        Furnitures(const Furnitures&){}
        Furnitures& operator=(const Furnitures&);
        
    private:
        SDL_Renderer* renderer;
        std::map<std::string, SDL_Rect> furnituresPixelDimensions;
        std::map<std::string, std::unique_ptr<Object>> furnituresBodyObject;
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
        
};
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Staff__) */
