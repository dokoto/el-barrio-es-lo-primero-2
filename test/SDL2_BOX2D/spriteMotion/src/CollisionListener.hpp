#ifndef __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__
#define __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <map>

namespace barrio {
    
    class CollisionListener : public b2ContactListener
    {
    private:
        std::vector<std::pair<b2Fixture*, b2Fixture*> > objectsCollisioned;
        
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        
        std::vector<std::pair<b2Fixture*, b2Fixture*> > getCollisionObjectsList(void) const
        {
            return objectsCollisioned;
        }
        
        void clearCollisionObjectList(void)
        {
            objectsCollisioned.clear();
        }
    };
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__CollisionListener__) */





