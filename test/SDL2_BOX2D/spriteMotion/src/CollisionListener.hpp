#ifndef __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__
#define __EL_BARRIO_ES_LO_PRIMERO__CollisionListener__

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <map>
#include <string>
#include "Names.hpp"
#include "Entities.hpp"

namespace barrio {
    
    class CollisionListener : public b2ContactListener
    {
    private:
        std::map<std::string, entity::TypeOfFixture> objectsCollisionedByNameVSTypeOfFixture;
        
    private:
        bool collisionRules(b2Fixture* fixtureA, b2Fixture* fixtureB);
        
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        
        
        entity::TypeOfFixture checkTypeOfFixtureOfCollisioner(const std::string& name)
        {
            auto it = objectsCollisionedByNameVSTypeOfFixture.find(name);
            if (it != objectsCollisionedByNameVSTypeOfFixture.end())
                return it->second;
            else return entity::FIX_NONE;
        }
        
        void clearCollisionObjectList(void)
        {
            objectsCollisionedByNameVSTypeOfFixture.clear();
        }
    };
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__CollisionListener__) */





