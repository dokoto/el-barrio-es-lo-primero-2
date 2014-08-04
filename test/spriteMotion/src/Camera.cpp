#include <cmath>
#include "Colors.hpp"
#include "Camera.hpp"
#include "errorsCodes.hpp"
#include "Constants.hpp"

namespace barrio {
    using namespace std;
    
    void Camera::CreateCamera(const float32 camera_width, const float32 camera_heigth,
                              const float32 world_width, const float32 world_height)
    {
        this->camera_position.x = 0;
        this->camera_position.y = 0;
        this->camera_width = camera_width;
        this->camera_height = camera_heigth;
        this->world_width = world_width;
        this->world_height = world_height;
        this->world_middle_height = this->world_height / 2;
        this->world_middle_width = this->world_width / 2;
        this->camera_middle_height = this->camera_height / 2;
        this->camera_middle_width = this->camera_width / 2;
        this->shift_factor = 0.05f;
        this->oldCartesianPosOfFollowSprite.x = 0.0f;
        this->oldCartesianPosOfFollowSprite.y = 0.0f;
    }
    
    Camera::~Camera(void)
    {
        spriteToFollow = nullptr;
        printf("Destroing Camera\n");
    }
    
    void Camera::renderBackGround(SDL_Renderer*& renderer)
    {
        if (this->background.isEmpty()) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Camera background not found");
            throw error::CAMERA_NO_BACKGROUND_FOUND;
        }
        else
        {
            if (this->spriteToFollow != nullptr)
            {                
                b2Vec2 cartesianPos = spriteToFollow->getPosition();
                SDL_Point ScreenPoint = this->convCartesianToScreen(cartesianPos);
                this->cameraFollowObj(ScreenPoint, this->camera_position);
            }
            else
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Camera has not an item to follow");
            }
            SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
            SDL_RenderClear( renderer );
            SDL_Rect clip {camera_position.x, camera_position.y, static_cast<int>(camera_width), static_cast<int>(camera_height)};
            this->render(SDL_Point{0, 0}, clip, renderer, &background);
        }
    }
    
    void Camera::renderAnimation(Animation animation, SDL_Renderer*& renderer, Texture* obj)
    {
        this->renderObj(animation.getCartesianPosition(), animation.getclipInPx(), renderer, obj);
    }
    
    void Camera::renderDebugInfo(SDL_Renderer*& renderer, DebugInfo* obj)
    {
        SDL_Rect renderQuad = { 10, 10, obj->getPixelWidth(), obj->getPixelHeight() };
        SDL_RenderCopy( renderer, obj->getTexture(), NULL, &renderQuad );
    }
    
    void Camera::renderObj(const b2Vec2& cartesianPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj)
    {
        SDL_Point ScreenPoint = this->convCartesianToScreen(cartesianPosition);
        
        if (ScreenPoint.x >= camera_position.x && ScreenPoint.x <= (camera_position.x + camera_width))
        {
            ScreenPoint.x = ScreenPoint.x - camera_position.x;
            this->render(ScreenPoint, clip, renderer, obj);
        }
        
    }
    
    void Camera::render(const SDL_Point& screenPosition, const SDL_Rect& clip, SDL_Renderer*& renderer, Texture* obj,
                        double angle, SDL_Point center, SDL_RendererFlip flip)
    {
        SDL_Rect renderQuad = { screenPosition.x, screenPosition.y, obj->getPixelWidth(), obj->getPixelHeight() };
        renderQuad.w = clip.w;
        renderQuad.h = clip.h;
        
        SDL_RenderCopyEx( renderer, obj->getSDLTexture(), &clip, &renderQuad, angle, &center, flip );
    }
    
    
    SDL_Point Camera::convCartesianToScreen(const b2Vec2& CartesianCoords)
    {
        SDL_Point ScreenCooeds;
        
        if (CartesianCoords.x < 0.0f)
        {
            float32 result = world_middle_width - ( std::abs(CartesianCoords.x) * consts::PHYSICS_CONV_FACTOR_PX);
            ScreenCooeds.x = static_cast<int>(result);
        }
        else
        {
            float32 result = world_middle_width + ( std::abs(CartesianCoords.x) * consts::PHYSICS_CONV_FACTOR_PX);
            ScreenCooeds.x = static_cast<int>(result);
        }
        
        if (CartesianCoords.y < 0)
        {
            float32 result = world_middle_height + ( std::abs(CartesianCoords.y) * consts::PHYSICS_CONV_FACTOR_PX);
            ScreenCooeds.y = static_cast<int>(result);
        }
        else
        {
            float32 result = world_middle_height - ( std::abs(CartesianCoords.y) * consts::PHYSICS_CONV_FACTOR_PX);
            ScreenCooeds.y = static_cast<int>(result);
        }
        
        return ScreenCooeds;
    }
    
    void Camera::cameraFollowObj(const SDL_Point& screenPosition, SDL_Point& camera_position)
    {
        if (camera_position.x + camera_width > screenPosition.x &&  camera_position.x <= screenPosition.x)
        {
            if ( (screenPosition.x - camera_position.x) < consts::CAMERA_MARGIN_PX)
            {
                if (camera_position.x > 0)
                {
                    if (camera_position.x - consts::CAMERA_MARGIN_PX > 0)
                    {
                        shift_factor = consts::CAMERA_MARGIN_PX - (screenPosition.x - camera_position.x);
                        camera_position.x -= shift_factor;
                    }
                    else
                    {
                        camera_position.x -= 1;
                    }
                }
            }
            else if ((screenPosition.x - camera_position.x) > (camera_width - consts::CAMERA_MARGIN_PX))
            {
                if ((world_width-camera_position.x) > camera_width)
                {
                    if (camera_position.x + camera_width < world_width - consts::CAMERA_MARGIN_PX)
                    {
                        shift_factor = std::abs((camera_width - consts::CAMERA_MARGIN_PX) - (screenPosition.x - camera_position.x));
                        camera_position.x += shift_factor;
                    }
                    else
                    {
                        camera_position.x += 1;
                    }
                }
            }
        }
        else
        {
            if (screenPosition.x < camera_middle_width)
            {
                camera_position.x = 0;
            }
            else if (world_width - screenPosition.x < camera_middle_width)
            {
                camera_position.x = static_cast<int>(world_width - camera_width);
            }
            else
            {
                camera_position.x = static_cast<int>(screenPosition.x - camera_middle_width);
            }
        }
    }
}