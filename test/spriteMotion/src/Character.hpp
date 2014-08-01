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
        Character(const std::string& name, SDL_Renderer*& lrenderer, Physics* world);
        ~Character();
        
        void loadAcctions(const std::string& spriteSheetsJsonPath, const std::string& spriteSheetsPngPath)
        {
            loadSpriteSheetsJson(spriteSheetsJsonPath);
            loadSpriteSheetsPng(spriteSheetsPngPath);
        }
        
        void addSpriteToWorld(const int x, const int y);
        void playAnimation(const std::string& animationName);
        void stopAnimation();
        void setVelocity(SDL_Point velocity);
        
    
    private:
        SDL_Renderer* renderer;
        int currentAnimationFrame;
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
