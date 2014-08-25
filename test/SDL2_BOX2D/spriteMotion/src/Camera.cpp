#include <cmath>
#include "Colors.hpp"
#include "Camera.hpp"
#include "errorsCodes.hpp"
#include "Utils.hpp"
#include "Furnitures.hpp"

namespace barrio {
    using namespace std;
    
    void Camera::CreateCamera(const SDL_Point& cameraPosition, const Size<int>& cameraSize)
    {
        this->cameraPosition = cameraPosition;
        this->cameraSize = std::move(cameraSize);
        this->cameraSizeMiddle = {this->cameraSize.w/2, this->cameraSize.h/2};
    }
    
    Camera::~Camera(void)
    {
        printf("Destroing Camera\n");
    }
    
    void Camera::cameraFollowObj(const SDL_Point& objPosition, SDL_Point& cameraPosition)
    {
        if (cameraPosition.x + cameraSize.w > objPosition.x &&  cameraPosition.x <= objPosition.x)
        {
            if ( (objPosition.x - cameraPosition.x) < consts::CAMERA_MARGIN_PX)
            {
                if (cameraPosition.x > 0)
                {
                    if (cameraPosition.x - consts::CAMERA_MARGIN_PX > 0)
                    {
                        shift_factor = consts::CAMERA_MARGIN_PX - (objPosition.x - cameraPosition.x);
                        cameraPosition.x -= shift_factor;
                    }
                    else
                    {
                        cameraPosition.x -= 1;
                    }
                }
            }
            else if ((objPosition.x - cameraPosition.x) > (cameraSize.w - consts::CAMERA_MARGIN_PX))
            {
                if ((consts::WORLD_WIDTH_PX-cameraPosition.x) > cameraSize.w)
                {
                    if (cameraPosition.x + cameraSize.w < consts::WORLD_WIDTH_PX - consts::CAMERA_MARGIN_PX)
                    {
                        shift_factor = abs( (cameraSize.w - consts::CAMERA_MARGIN_PX) - (objPosition.x - cameraPosition.x) );
                        cameraPosition.x += shift_factor;
                    }
                    else
                    {
                        cameraPosition.x += 1;
                    }
                }
            }
        }
        else
        {
            if (objPosition.x < cameraSizeMiddle.w)
            {
                cameraPosition.x = 0;
            }
            else if (consts::WORLD_WIDTH_PX - objPosition.x < cameraSizeMiddle.w)
            {
                cameraPosition.x = static_cast<int>(consts::WORLD_WIDTH_PX - cameraSize.w);
            }
            else
            {
                cameraPosition.x = static_cast<int>(objPosition.x - cameraSizeMiddle.w);
            }
        }
    }
}