#ifndef __EL_BARRIO_ES_LO_PRIMERO__Game__
#define __EL_BARRIO_ES_LO_PRIMERO__Game__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Colors.hpp"

namespace barrio {
    
    class Game
    {        
    public:
        Game();
        ~Game();
        void gameLoop(void);
        
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        SDL_Window* window;
        SDL_Renderer* renderer;        
        
    private:
        void loadMedia(void);
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Game__) */
