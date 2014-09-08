#ifndef __EL_BARRIO_ES_LO_PRIMERO__Controller__
#define __EL_BARRIO_ES_LO_PRIMERO__Controller__

#include <SDL2/SDL.h>
#include "Physics.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Furnitures.hpp"
#include "Text.hpp"
#include "LevelsFactory.hpp"


namespace barrio
{
    class Controller
    {
    public:        
        Controller(void) : currentLevel(nullptr) {}
        ~Controller(void);
        void CreateController(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts);
        void loadLevelWord(const LevelsFactory::Stage stage);
        bool handleSystem(void);
        void releaseClycleLiveTimeResources(void);
                
    private:
        Controller(const Controller&);
        Controller& operator=(const Controller&&);
        
    private:
        bool handleGameState(SDL_Event* event);
        
    private:
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        Camera* camera;
        Text* texts;
        SDL_Event event;
        Level* currentLevel;
        LevelsFactory levelFactory;                
        
    };
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Controller__) */


