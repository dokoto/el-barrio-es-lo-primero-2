#ifndef __EL_BARRIO_ES_LO_PRIMERO__Staff__
#define __EL_BARRIO_ES_LO_PRIMERO__Staff__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"
#include "Clip.hpp"

namespace barrio {
    
    class Furnitures : public Sprite
    {
    public:
        void CreateFurnitures(const std::string& FurnituresName, SDL_Renderer*& lrenderer, Physics* physicsWorld, SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0});
        Furnitures(): renderer(nullptr) {}
        ~Furnitures() {}
        
        void loadFurnitures(const std::string& jsonSheetPath, const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadJsonSheet(jsonSheetPath, zoomX, zoomY);
            loadPngSheet(pngSheetPath, zoomX, zoomY);
        }
        
        void addToPhysicsWorld(const std::string& furnitureElemenName, const float32 cartesianPosX, const float32 cartesianPosY);
        Clip getFurnitureClip(const std::string& furnitureElemenName);
        
        void setToFlip(bool flip);
        bool getToFlip(void) const;
        
    private:
        
        Furnitures(const Furnitures&){}
        Furnitures& operator=(const Furnitures&);
        
    private:
        SDL_Renderer* renderer;
        std::map<std::string, SDL_Rect> furnituresPixelDimensions;
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
        
};
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Staff__) */
