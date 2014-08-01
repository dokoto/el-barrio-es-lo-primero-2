#ifndef __EL_BARRIO_ES_LO_PRIMERO__Game__
#define __EL_BARRIO_ES_LO_PRIMERO__Game__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Colors.hpp"
#include "Physics.hpp"

namespace barrio {
    
    class Game
    {        
    public:
        Game();
        ~Game();
        void gameLoop(void);
        
    private:
        static constexpr int SCREEN_WIDTH = 800;
        static constexpr int SCREEN_HEIGHT = 600;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        
    private:
        void loadMedia(void);
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Game__) */
