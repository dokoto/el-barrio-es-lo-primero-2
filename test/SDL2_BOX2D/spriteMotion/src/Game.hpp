#ifndef __EL_BARRIO_ES_LO_PRIMERO__Game__
#define __EL_BARRIO_ES_LO_PRIMERO__Game__

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Physics.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "DebugInfo.hpp"
#include "Furnitures.hpp"

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
        Camera camera;
        Character players[2];
        Furnitures furnitures;
        DebugInfo debugInfo;
        
    private:
        void loadMedia(void);
        std::string createDebugText();
        void handleKeyBoard1(std::string& action, b2Vec2& velocity);
        void handleKeyBoard2(std::string& action, b2Vec2& velocity);
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Game__) */
