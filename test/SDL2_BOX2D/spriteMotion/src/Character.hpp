#ifndef __EL_BARRIO_ES_LO_PRIMERO__Player__
#define __EL_BARRIO_ES_LO_PRIMERO__Player__

#include <string>
#include <map>
#include <vector>

#include "Sprite.hpp"
#include "Animation.hpp"

namespace barrio {
    
    class Character : public Sprite
    {
    public:
        void CreateCharacter(const std::string& name, SDL_Renderer*& lrenderer, Physics* physicsWorld);
        Character(): renderer(nullptr) {}
        ~Character() {}
        
        void loadAnimations(const std::string& spriteSheetsJsonPath, const std::string& spriteSheetsPngPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadSpriteSheetsJson(spriteSheetsJsonPath, zoomX, zoomY);
            loadSpriteSheetsPng(spriteSheetsPngPath, zoomX, zoomY);
        }
        
        void addToPhysicsWorld(const float32 cartesianPosX, const float32 cartesianPosY);
        Animation playAnimation(const std::string& animationName, const size_t delayInFrames);
        void stopAnimation();
        void setVelocity(b2Vec2 velocity);
        
    private:
        
        Character(const Character&){}
        Character& operator=(const Character&);
    
    private:
        SDL_Renderer* renderer;
        size_t currentAnimationFrame, delayFrameCount;
        std::string currentAnimation;
        std::map<std::string, std::vector<SDL_Rect>> animations;
        
        void loadSpriteSheetsJson(const std::string& spriteSheetsJsonPath, const double zoomX = 1.0, const double zoomY = 1.0);
        void loadSpriteSheetsPng(const std::string& spriteSheetsPngPath, const double zoomX = 1.0, const double zoomY = 1.0)
        {
            loadFromFile(spriteSheetsPngPath, renderer, zoomX, zoomY);
        }
    };
    
}


#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Player__) */
