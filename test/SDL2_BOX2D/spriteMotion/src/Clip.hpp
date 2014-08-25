
#ifndef EL_BARRIO_ES_LO_PRIMERO_Animation_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Animation_hpp

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>

class Clip
{
private:
    Clip(const Clip&){}
    Clip& operator=(const Clip&);
    
public:
    std::string name;
    SDL_Rect screenOrigin;
    SDL_Rect screenDestination;
    float32 destinationAngle;

    
public:
    Clip(void) {}
    Clip(std::string name, SDL_Rect screenOrigin, SDL_Rect screenDestination, float32 destinationAngle = 0.0f)
    : name(std::move(name)), screenOrigin(std::move(screenOrigin)), screenDestination(std::move(screenDestination)), destinationAngle(std::move(destinationAngle))
    {
    };
    
    Clip(const Clip&& c): name(std::move(c.name)), screenOrigin(std::move(c.screenOrigin)), screenDestination(std::move(c.screenDestination)), destinationAngle(std::move(c.destinationAngle)) {};
    Clip& operator=(const Clip&& c)
    {
        name = std::move(name);
        screenOrigin = std::move(c.screenOrigin);
        screenDestination = std::move(c.screenDestination);
        destinationAngle = std::move(c.destinationAngle);
        return *this;
    }
   
};

#endif
