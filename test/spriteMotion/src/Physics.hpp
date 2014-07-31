#ifndef __EL_BARRIO_ES_LO_PRIMERO__Physics__
#define __EL_BARRIO_ES_LO_PRIMERO__Physics__

#include <vector>
#include <Box2D/Box2D.h>
#include "Texture.hpp"

namespace barrio {
    
    class Physics
    {
    public:
        Physics(const float gravityX, const float gravityY);
        ~Physics(void);
        void addPolygon(Texture& body);
    private:
        b2Vec2 gravity;
        b2World* world;
        std::vector<b2Body*> bodies;
    };
    
}
#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Physics__) */
