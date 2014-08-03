#ifndef __EL_BARRIO_ES_LO_PRIMERO__Physics__
#define __EL_BARRIO_ES_LO_PRIMERO__Physics__

#include <map>
#include <utility>
#include <string>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>


namespace barrio {
    
    class Physics
    {
    public:
        Physics(const b2Vec2 gravity, const int lwidth, const int lheight);
        ~Physics(void);
        void addSpritePolygon(const std::string& spriteName, const float spriteWidth, const float spriteHeight, const b2Vec2& spritePosition);
        void Step(void)
        {
            world->Step(timeStep, this->velocityIterations, this->positionIterations);
        }
        float32 convPixelsToCartesian(const int pixels)
        {
            return pixels / RATIO_CONV;
        }
        b2Body* getBody(const std::string& spriteNamme);

    private:
        b2Vec2 gravity;
        b2World* world;
        int width, height;
        std::map<std::string, b2Body*> bodies;
        static constexpr float32 frequency = 60.0f;
        static constexpr int32 velocityIterations = 8;
        static constexpr int32 positionIterations = 3;
        static constexpr float32 timeStep = 1.0f / frequency;
        /*
         * Ratio de conversion entre las coordenadas de Box2D y SDL2.
         * La cosa es que en Box2D las unidades equivalen a metros( 1 unidad == 1 metro)
         * Con el ratio de conversion lo que hacemos es convetirlas desde y hacia pixeles
         * Si una unidad es un metro, podemos decir que una metro son 50 pixeles, quedando
         * 1 metro == 50px, se deberia ajustar este ratio en funcion del ancho de la pantalla
         */
        static constexpr float32 RATIO_CONV = 50.0f;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Physics__) */
