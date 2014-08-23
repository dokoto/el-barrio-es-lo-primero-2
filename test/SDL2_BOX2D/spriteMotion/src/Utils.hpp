#ifndef EL_BARRIO_ES_LO_PRIMERO_Utils_h
#define EL_BARRIO_ES_LO_PRIMERO_Utils_h

#include <cmath>

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "Constants.hpp"
#include "Size.hpp"

namespace barrio {
    class Utils
    {
    public:
        
        static constexpr float M2P = 20;
        static constexpr float P2M = 1/M2P;
        
        static b2Vec2 convScreenPosToCartesianPos(const SDL_Point& screenPosCoords)
        {
            return b2Vec2 {screenPosCoords.x*P2M, screenPosCoords.y*P2M};
        }
        
        static Size<float32> convSreenSizeToCartesianSize(const Size<int>& cartesianSize)
        {
            return Size<float32> {static_cast<float32>((P2M*cartesianSize.w)/2), static_cast<float32>((P2M*cartesianSize.h)/2)};
        }
        
        static SDL_Point convCartesianPosToScreennPos(const b2Vec2& castesianPosCoords)
        {
            return SDL_Point{static_cast<int>(castesianPosCoords.x*M2P), static_cast<int>(castesianPosCoords.y*M2P)};
        }
        
        static void rotateTranslate(b2Vec2& vector, const b2Vec2& center, float angle)
        {
            b2Vec2 tmp;
            tmp.x=vector.x*cos(angle)-vector.y*sin(angle);
            tmp.y=vector.x*sin(angle)+vector.y*cos(angle);
            vector=tmp+center;
        }
        
        
        /*
        
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
         */
        
    };
}


#endif
