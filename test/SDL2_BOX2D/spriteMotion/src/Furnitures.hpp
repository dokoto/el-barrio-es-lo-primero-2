#ifndef __EL_BARRIO_ES_LO_PRIMERO__Staff__
#define __EL_BARRIO_ES_LO_PRIMERO__Staff__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"
#include "Clip.hpp"

namespace barrio {
    
    class furnituresBodies
    {
    public:
        SDL_Rect clip;
        b2Body* body;
    };
    
    class Furnitures : public Sprite
    {
    public:
        void CreateFurnitures(const std::string& name, SDL_Renderer*& lrenderer, Physics* physicsWorld);
        Furnitures(): renderer(nullptr) {}
        ~Furnitures() {}
        
        void loadFurnitures(const std::string& jsonSheetPath, const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadJsonSheet(jsonSheetPath, zoomX, zoomY);
            loadPngSheet(pngSheetPath, zoomX, zoomY);
        }
        
        void addToPhysicsWorld(const std::string& furnitureName, const float32 cartesianPosX, const float32 cartesianPosY);
        Clip getFurnitureClip(const std::string& furnitureName);
        
    private:
        
        Furnitures(const Furnitures&){}
        Furnitures& operator=(const Furnitures&);
        
    private:
        SDL_Renderer* renderer;
        std::map<std::string, furnituresBodies> furnitures;
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
        
};
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Staff__) */
