
#ifndef EL_BARRIO_ES_LO_PRIMERO_Animation_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Animation_hpp

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

namespace barrio
{
class Clip
{
public:
    enum Side {LEFT_SIDE, RIGHT_SIDE};
    
private:
    Clip(const Clip&){}
    Clip& operator=(const Clip&);
    
private:
    std::string name;
    SDL_Rect originClip;
    Side side;

    
public:
    Clip(void) { }
    Clip(const std::string& name, const SDL_Rect& originClip, Side side = Side::RIGHT_SIDE ) : name(name), originClip(originClip), side(side) { }    
    Clip(const Clip&& c): name(c.name), originClip(c.originClip), side(c.side) { }
    Clip& operator=(const Clip&& c)
    {
        this->name = c.name;
        this->originClip = c.originClip;
        this->side = c.side;
        
        return *this;
    }
   
};
}
#endif
