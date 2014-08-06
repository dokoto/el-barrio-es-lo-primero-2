#ifndef EL_BARRIO_ES_LO_PRIMERO_Utils_h
#define EL_BARRIO_ES_LO_PRIMERO_Utils_h

#include <cmath>

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "Constants.hpp"

namespace barrio {
    class Utils
    {
    public:
        static b2Vec2 convScreenToCartesian(const SDL_Rect& ScreenCoords)
        {
            b2Vec2 CartesianCoords;
            
            CartesianCoords.x = convXScreenToCartesian(ScreenCoords.x);
            CartesianCoords.y = convYScreenToCartesian(ScreenCoords.y);
            
            return CartesianCoords;
        }
        
        static SDL_Point convCartesianToScreen(const b2Vec2& CartesianCoords)
        {
            SDL_Point ScreenCoords;
            
            ScreenCoords.x = convXCartesianToScreen(CartesianCoords.x);
            ScreenCoords.y = convYCartesianToScreen(CartesianCoords.y);
            
            return ScreenCoords;
        }
        
        
        
        static float32 convXScreenToCartesian(const int ScreenXCoord)
        {
            if (ScreenXCoord < consts::WORLD_MIDDLE_WIDTH_PX)
            {
                return - ( static_cast<float32>(ScreenXCoord) / consts::PHYSICS_CONV_FACTOR_PX);
            }
            else if (ScreenXCoord == consts::WORLD_MIDDLE_WIDTH_PX)
                return 0.0f;
            else
            {
                return  ( static_cast<float32>(ScreenXCoord) / consts::PHYSICS_CONV_FACTOR_PX);
            }
        }
        
        static float32 convYScreenToCartesian(const int ScreenYCoord)
        {
            if (ScreenYCoord < consts::WORLD_MIDDLE_HEIGHT_PX)
            {
                return static_cast<float32>(ScreenYCoord) / consts::PHYSICS_CONV_FACTOR_PX;
            }
            else if (ScreenYCoord == consts::WORLD_MIDDLE_HEIGHT_PX)
                return 0.0f;
            else
            {
                return  - (static_cast<float32>(ScreenYCoord) / consts::PHYSICS_CONV_FACTOR_PX);
            }
        }
        
        
        static int convXCartesianToScreen(const float32 CartesianXCoord)
        {
            if (CartesianXCoord < 0.0f)
            {
                float32 result = consts::WORLD_MIDDLE_WIDTH_PX - ( std::abs(CartesianXCoord) * consts::PHYSICS_CONV_FACTOR_PX);
                return static_cast<int>(result);
            }
            else if (CartesianXCoord == 0.0f)
                return static_cast<int>(consts::WORLD_MIDDLE_WIDTH_PX);
            else
            {
                float32 result = consts::WORLD_MIDDLE_WIDTH_PX + ( std::abs(CartesianXCoord) * consts::PHYSICS_CONV_FACTOR_PX);
                return static_cast<int>(result);
            }
            
        }
        
        
        static int convYCartesianToScreen(const float32 CartesianYCoord)
        {
            if (CartesianYCoord < 0.0f)
            {
                float32 result = consts::WORLD_MIDDLE_HEIGHT_PX + ( std::abs(CartesianYCoord) * consts::PHYSICS_CONV_FACTOR_PX);
                return static_cast<int>(result);
            }
            else if (CartesianYCoord == 0.0f)
                return static_cast<int>(consts::WORLD_MIDDLE_HEIGHT_PX);
            else
            {
                float32 result = consts::WORLD_MIDDLE_HEIGHT_PX - ( std::abs(CartesianYCoord) * consts::PHYSICS_CONV_FACTOR_PX);
                return static_cast<int>(result);
            }
            
        }
        
        static int convWidthCartesianToScreen(const float32 CartesianWidth)
        {
            return static_cast<int>(CartesianWidth * consts::PHYSICS_CONV_FACTOR_PX);
        }
        
        static int convHeightCartesianToScreen(const float32 CartesianHeight)
        {
            return static_cast<int>(CartesianHeight * consts::PHYSICS_CONV_FACTOR_PX);
        }
        
        static float32 convWidthScreenToCartesian(const int ScreenWidth)
        {
            return static_cast<float32>(ScreenWidth / consts::PHYSICS_CONV_FACTOR_PX);
        }
        
        static float32 convHeightScreenToCartesian(const int ScreenHeight)
        {
            return static_cast<float32>(ScreenHeight / consts::PHYSICS_CONV_FACTOR_PX);
        }
        
    };
}


#endif
