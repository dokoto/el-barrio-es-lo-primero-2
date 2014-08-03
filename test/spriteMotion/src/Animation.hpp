
#ifndef EL_BARRIO_ES_LO_PRIMERO_Animation_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Animation_hpp

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

class Animation
{
private:
    Animation(const Animation&){}
    Animation& operator=(const Animation&);
    b2Vec2 cartesianPosition;
    SDL_Rect clipInPx;
    
public:
    Animation(b2Vec2 lcartesianPosition, SDL_Rect lclipInPx) : cartesianPosition(lcartesianPosition), clipInPx(lclipInPx) {};
    Animation(const Animation&& a): cartesianPosition(a.cartesianPosition), clipInPx(a.clipInPx) {};
    const b2Vec2& getCartesianPosition() { return cartesianPosition; }
    const SDL_Rect& getclipInPx() { return clipInPx; }
};

#endif
