#ifndef __EL_BARRIO_ES_LO_PRIMERO__Game__
#define __EL_BARRIO_ES_LO_PRIMERO__Game__

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Physics.hpp"
#include "Render.hpp"
#include "Controller.hpp"
#include "Text.hpp"
#include "Camera.hpp"
#include "FrameRate.hpp"

namespace barrio {
    
    class Game
    {        
    public:
        Game();
        ~Game();
        void gameLoop(void);
        
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Physics physicsWorld;
        Controller controller;
        Render render;
        Camera camera;
        utls::FrameRate frameRate;
        Text texts;
        
    private:
        void loadMedia(void);
        std::string createDebugText();        
        void handleKeyBoard1(std::string& action, b2Vec2& velocity);
        void handleKeyBoard2(std::string& action, b2Vec2& velocity);
        bool handlePoolEvents(SDL_Event* e);
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Game__) */
