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
        
        static void rotateTranslate(b2Vec2& vector, const b2Vec2& center, float32 angle)
        {
            b2Vec2 tmp;
            
            tmp.x = ( vector.x * cosf(angle) ) - ( vector.y * sinf(angle) );
            tmp.y = ( vector.x * sinf(angle) ) + ( vector.y * cosf(angle) );
            
            vector = tmp + center;
        }
        
        static SDL_Point fullConversionCartesianPosToScreenPos(b2Fixture* fixture, const b2Vec2& worldCenter, float32 angle)
        {
            b2Vec2 point = {0, 0};
            if (fixture->GetType() == b2Shape::e_polygon)
                point = ((b2PolygonShape*)fixture->GetShape())->GetVertex(0);
            else  if (fixture->GetType() == b2Shape::e_circle)
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Convertion Physics: Circle is not implemented, yet");
            else
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Convertion Physics: Shape no implemented");
            
            Utils::rotateTranslate(point, worldCenter, angle);
            
            return Utils::convCartesianPosToScreennPos(point);
        }        
    };
}


#endif
