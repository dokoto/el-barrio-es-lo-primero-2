#ifndef __EL_BARRIO_ES_LO_PRIMERO__Player__
#define __EL_BARRIO_ES_LO_PRIMERO__Player__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"
#include "Names.hpp"
#include "Glob.hpp"

namespace barrio {
    
    class Character : public Sprite
    {
    public:
        void CreateCharacter(const std::string& name, entity::TypeOfSprite typeOfSprite, entity::TypeOfShape typeOfShape,  entity::TypeOfFixture typeOfFixture,
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
            return (currentAnimationName.compare(name::MOVEMENT_STOP) == 0);
        }
        
        Size<int> getAnimationSize(const std::string& animationName)
        {
            return Size<int> {animations[animationName].at(0).w, animations[animationName].at(0).h};
        }
        
        void setSide(Glob::Side side);
        bool getSide(void) const;
        void playAnimation(const std::string& animationName, const size_t delayInFrames);
        SDL_Rect getCurrentClip(void)
        {
            if (this->currentAnimationName.empty())
            {
                return animations[name::MOVEMENT_STOP].at(0);
            }
            return animations[this->currentAnimationName].at(currentAnimationFrame);
        }
        void stopAnimation();
        std::string getTarget(void) { return this->enemyTarget; }
        void setTarget(const std::string& enemyTarget) { this->enemyTarget = enemyTarget; }
        Glob::AIMode getAIMode(void) { return this->aiMode; }
        void setAIMode(Glob::AIMode aiMode) { this->aiMode = aiMode; }
        int getLive(void) { return this->live; }
        void setLive(const int live) { this->live = live; }
                
    private:
        
        Character(const Character&){}
        Character& operator=(const Character&);
    
    private:
        SDL_Renderer* renderer;
        size_t currentAnimationFrame, delayFrameCount;
        std::string currentAnimationName;
        std::map<std::string, std::vector<SDL_Rect>> animations;
        std::string enemyTarget;
        Glob::AIMode aiMode;        
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        inline void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
    };
    
}


#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Player__) */
