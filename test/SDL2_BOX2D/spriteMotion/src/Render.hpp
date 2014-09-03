#ifndef __EL_BARRIO_ES_LO_PRIMERO__Render__
#define __EL_BARRIO_ES_LO_PRIMERO__Render__

#include <vector>
#include <SDL2/SDL.h>
#include "Physics.hpp"
#include "Camera.hpp"
#include "Text.hpp"

namespace barrio {
    
    
    class Render
    {
    public:
        Render():renderer(nullptr), physicsWorld(nullptr), camera(nullptr) {}
        ~Render() {}
        void CreateRender(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts);
        
        void draw(void);
        void drawDebugPrimitives(float avgFPS = 0.0f);
        void drawDebug(float avgFPS = 0.0f);
        
    private:
        void clearScreen(void);
        void step(void);
        void drawBackGround(void);
        void drawCharacters(void);
        void drawEnemies(void);
        void drawFurnitures(void);
        void drawPhysicWorld(void);
        void drawDebugText(float avgFPS);
        
    private:
        SDL_Renderer* renderer;
        Physics* physicsWorld;
        Camera* camera;
        Text* texts;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Render__) */


