#ifndef __EL_BARRIO_ES_LO_PRIMERO__Camera__
#define __EL_BARRIO_ES_LO_PRIMERO__Camera__

#include <memory>
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace barrio {
    
    class Camera
    {
        
    public:
        Camera(const float32 camera_width, const float32 camera_heigth, const float32 world_width, const float32 world_height);
        ~Camera();
        void renderBackGround(SDL_Renderer*& renderer);
        void renderObj(const b2Vec2& cartesianPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj);
        void renderAnimation(Animation animation, SDL_Renderer*& renderer, Texture* obj);
        void follow(std::shared_ptr<Sprite> spriteToFollow){
            this->spriteToFollow = spriteToFollow;
            oldCartesianPosOfFollowSprite = spriteToFollow->getPosition();
        }
        SDL_Point convCartesianToScreen(const b2Vec2& CartesianCoords);
        void cameraFollowObj(const SDL_Point& screenPosition, SDL_Point& camera_position);
                
        inline void setBackground(const std::string& backGroundPath, SDL_Renderer*& renderer)
        {
            background->loadFromFile(backGroundPath, renderer);
        }
        
        
    private:
        SDL_Point camera_position;
        float32 camera_width;
        float32 camera_middle_width;
        float32 camera_height;
        float32 camera_middle_height;
        float32 world_width;
        float32 world_middle_width;
        float32 world_height;
        float32 world_middle_height;
        static constexpr float32 conversion_factor = 50;
        static constexpr int camera_margin = 100;
        float32 shift_factor;
        std::shared_ptr<Sprite> spriteToFollow;
        std::unique_ptr<Texture> background;
        b2Vec2 oldCartesianPosOfFollowSprite;
        
        void render(const SDL_Point& screenPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Camera__) */


