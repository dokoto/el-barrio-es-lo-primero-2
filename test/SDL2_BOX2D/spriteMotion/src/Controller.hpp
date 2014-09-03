#ifndef __EL_BARRIO_ES_LO_PRIMERO__Controller__
#define __EL_BARRIO_ES_LO_PRIMERO__Controller__

#include <SDL2/SDL.h>
#include "Physics.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Furnitures.hpp"
#include "Text.hpp"


namespace barrio
{
    class Controller
    {
    public:
        enum Level {LEVEL1};
        Controller(void): renderer(nullptr), physicsWorld(nullptr), camera(nullptr) {}
        ~Controller(void) {}
        void CreateController(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts);
        void loadLevelWord(const Level level);
        bool handleSystem(void);
        
        
    private:
        
        Controller(const Controller&);
        Controller& operator=(const Controller&&);
        
    private:
        bool handleGameState(SDL_Event* event);
        void handleInputPlayer(Character& player);
        
    private:
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        Camera* camera;
        Text* texts;
        SDL_Event event;
        Character playerA, playerB;
        Furnitures furnitures;
        
    };
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Controller__) */


