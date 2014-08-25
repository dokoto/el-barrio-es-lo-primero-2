#ifndef __EL_BARRIO_ES_LO_PRIMERO__Render__
#define __EL_BARRIO_ES_LO_PRIMERO__Render__

#include <SDL2/SDL.h>
#include "Physics.hpp"
#include "Camera.hpp"

namespace barrio {
    
    
    class Render
    {
    public:
        Render():renderer(nullptr), physicsWorld(nullptr), camera(nullptr) {}
        ~Render() {}
        void CreateRender(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera);
        
        void drawDebug(void);
        void draw(void);
        
    private:
        void clearScreen(void);
        void step(void);
        void drawBackGround(void);
        void drawCharacters(void);
        void drawEnemies(void);
        void drawFurnitures(void);
        void drawPhysicWorld(void);
        
    private:
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        Camera* camera;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Render__) */


