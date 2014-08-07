#ifndef __EL_BARRIO_ES_LO_PRIMERO__Player__
#define __EL_BARRIO_ES_LO_PRIMERO__Player__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"
#include "Clip.hpp"

namespace barrio {
    
    class Character : public Sprite
    {
    public:
        void CreateCharacter(const std::string& name, SDL_Renderer*& lrenderer, Physics* physicsWorld, SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0});
        Character(): renderer(nullptr) {}
        ~Character() {}
        
        inline void loadAnimations(const std::string& jsonSheetpath, const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadJsonSheet(jsonSheetpath, zoomX, zoomY);
            loadPngSheet(pngSheetPath, zoomX, zoomY);
        }
        
        inline const b2Vec2 getVelocity(void) const
        {
            return getPhysicsBody(getSpriteName())->GetLinearVelocity();
        }
        
        inline void setVelocity(const b2Vec2& velocity)
        {
            getPhysicsBody(getSpriteName())->SetLinearVelocity(velocity);
        }
        
        inline const b2Vec2 getPosition(void)
        {
            return getPhysicsBody(getSpriteName())->GetPosition();
        }
        
        void addToPhysicsWorld(const float32 cartesianPosX, const float32 cartesianPosY);
        Clip playAnimation(const std::string& animationName, const size_t delayInFrames);
        void stopAnimation();
        
    private:
        
        Character(const Character&){}
        Character& operator=(const Character&);
    
    private:
        SDL_Renderer* renderer;
        size_t currentAnimationFrame, delayFrameCount;
        std::string currentAnimation;
        std::map<std::string, std::vector<SDL_Rect>> animations;
        
        void loadJsonSheet(const std::string& jsonSheetPath, const double zoomX = 1.0, const double zoomY = 1.0);
        inline void loadPngSheet(const std::string& pngSheetPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(pngSheetPath, renderer, zoomX, zoomY);
        }
    };
    
}


#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Player__) */
