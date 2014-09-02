#ifndef __EL_BARRIO_ES_LO_PRIMERO__Player__
#define __EL_BARRIO_ES_LO_PRIMERO__Player__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"

namespace barrio {
    
    class Character : public Sprite
    {
    public:
        void CreateCharacter(const std::string& name, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape,  Object::TypeOfFixture typeOfFixture,
                             SDL_Renderer*& renderer, SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0});
        Character(): renderer(nullptr) {}
        ~Character() {}
        
        inline void loadAnimations(const std::string& jsonSheetpath, const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadJsonSheet(jsonSheetpath, zoomX, zoomY);
            loadPngSheet(pngSheetPath, zoomX, zoomY);
        }
        
        inline bool isAnimationStop(void)
        {
            return currentAnimationName.empty();
        }
        
        Size<int> getAnimationSize(const std::string& animationName)
        {
            return Size<int> {animations[animationName].at(0).w, animations[animationName].at(0).h};
        }
        
        void setToFlip(bool flip);
        bool getToFlip(void) const;
        void playAnimation(const std::string& animationName, const size_t delayInFrames);
        SDL_Rect getCurrentClip(void)
        {
            return animations[this->currentAnimationName].at(currentAnimationFrame);
        }
        void stopAnimation();
        
    private:
        
        Character(const Character&){}
        Character& operator=(const Character&);
    
    private:
        SDL_Renderer* renderer;
        size_t currentAnimationFrame, delayFrameCount;
        std::string currentAnimationName;
        std::map<std::string, std::vector<SDL_Rect>> animations;
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        inline void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
    };
    
}


#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Player__) */
