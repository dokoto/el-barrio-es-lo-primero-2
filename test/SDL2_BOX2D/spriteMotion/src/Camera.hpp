#ifndef __EL_BARRIO_ES_LO_PRIMERO__Camera__
#define __EL_BARRIO_ES_LO_PRIMERO__Camera__

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Size.hpp"
#include "Sprite.hpp"
#include "Constants.hpp"

namespace barrio {
    
    class Camera
    {
        
    public:
        Camera() : shift_factor(consts::CAMERA_SHIFT_FACTOR) {}
        ~Camera();
        void CreateCamera(const SDL_Point& cameraPosition, const Size<int>& cameraSize);
        
        void loadBackGroundImage(const std::string& backGroundPath, SDL_Renderer*& renderer)
        {
            backGround.setTransparentColor(SDL_Color{0xFF, 0xFF, 0xFF, 0});
            backGround.loadFromFile(backGroundPath, renderer);
        }
        void cameraFollowObj(const SDL_Point& objPosition, SDL_Point& camera_position);
        
    private:
        Camera(const Camera&){}
        Camera& operator=(const Camera&);
        int shift_factor;
        
    public:
        SDL_Point cameraPosition;
        Size<int> cameraSize;
        Size<int> cameraSizeMiddle;
        Sprite backGround;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Camera__) */


