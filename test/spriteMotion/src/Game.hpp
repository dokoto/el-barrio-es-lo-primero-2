#ifndef __EL_BARRIO_ES_LO_PRIMERO__Game__
#define __EL_BARRIO_ES_LO_PRIMERO__Game__

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Colors.hpp"
#include "Physics.hpp"
#include "Camera.hpp"
#include "Character.hpp"

namespace barrio {
    
    class Game
    {        
    public:
        Game();
        ~Game();
        void gameLoop(void);
        
    private:
        static constexpr int CAMERA_WIDTH = 800;
        static constexpr int CAMERA_HEIGHT = 600;
        static constexpr int WORLD_WIDTH = 1679;
        static constexpr int WORLD_HEIGHT = 600;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        std::unique_ptr<Camera> camera;
        std::shared_ptr<Character> player;
        
    private:
        void loadMedia(void);
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Game__) */
