#ifndef __EL_BARRIO_ES_LO_PRIMERO__Camera__
#define __EL_BARRIO_ES_LO_PRIMERO__Camera__

#include "Texture.hpp"
#include "Sprite.hpp"
#include "Clip.hpp"
#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "DebugInfo.hpp"

namespace barrio {
    
    class Camera
    {
        
    public:
        void CreateCamera(const float32 camera_width, const float32 camera_heigth,
                     const float32 world_width, const float32 world_height);
        Camera() : spriteToFollow(nullptr) {}
        ~Camera();
        
        void renderBackGround(SDL_Renderer*& renderer);
        void renderObj(const b2Vec2& cartesianPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj);
        void renderDebugInfo(SDL_Renderer*& renderer, DebugInfo* obj);
        void renderClip(Clip clip, SDL_Renderer*& renderer, Texture* obj);
        void cameraFollowObj(const SDL_Point& screenPosition, SDL_Point& camera_position);
        
        void follow(Sprite* spriteToFollow)
        {
            this->spriteToFollow = spriteToFollow;
            oldCartesianPosOfFollowSprite = spriteToFollow->getPosition();
        }
        
        void setBackground(const std::string& backGroundPath, SDL_Renderer*& renderer)
        {
            background.loadFromFile(backGroundPath, renderer);
        }
        
        void switchHorizontalFlip(void) { flip = SDL_FLIP_HORIZONTAL; };
        void switchVerticalFlip(void) { flip = SDL_FLIP_VERTICAL; };
        void switchFlipOFF() { flip = SDL_FLIP_NONE; };
        SDL_RendererFlip getFlip(void) { return flip; }
        
        SDL_Point getCenter(void) { return center; }
        void setCenter(SDL_Point center) { this->center = center; }
        double getAngle(void) { return angle; }
        void setAngle(double angle) { this->angle = angle; }
        
    private:
        Camera(const Camera&){}
        Camera& operator=(const Camera&);                
        
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
        float32 shift_factor;
        double angle;
        SDL_Point center;
        SDL_RendererFlip flip;
        Sprite* spriteToFollow;
        Texture background;
        b2Vec2 oldCartesianPosOfFollowSprite;
        
        void render(const SDL_Point& screenPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj,
                    double angle = 0.0, SDL_Point center = {0, 0}, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Camera__) */


