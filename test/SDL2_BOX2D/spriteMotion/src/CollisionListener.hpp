#ifndef __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__
#define __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <map>

namespace barrio {
    
    class CollisionListener : public b2ContactListener
    {
    public:
        std::vector<std::pair<b2Fixture*, b2Fixture*> > ObjectsCollisioned;
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    };
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__CollisionListener__) */



