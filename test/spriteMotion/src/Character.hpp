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
        Character(const std::string& name, SDL_Renderer*& lrenderer);
        ~Character();
        
        void loadAnimations(const std::string& spriteSheetsJsonPath, const std::string& spriteSheetsPngPath)
        {
            loadSpriteSheetsJson(spriteSheetsJsonPath);
            loadSpriteSheetsPng(spriteSheetsPngPath);
        }
        
        Animation playAnimation(const std::string& animationName, const size_t delayInFrames);
        void stopAnimation();
        void setVelocity(b2Vec2 velocity);
        
    
    private:
        SDL_Renderer* renderer;
        size_t currentAnimationFrame, delayFrameCount;
        std::string currentAnimation;
        std::map<std::string, std::vector<SDL_Rect>> animations;
        
        void loadSpriteSheetsJson(const std::string& spriteSheetsJsonPath);
        void loadSpriteSheetsPng(const std::string& spriteSheetsPngPath)
        {
            Texture::loadFromFile(spriteSheetsPngPath, renderer);
        }
    };
    
}


#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Player__) */
