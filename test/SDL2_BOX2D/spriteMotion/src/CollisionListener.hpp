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
        std::map< std::pair<std::string, entity::TypeOfFixture>, std::pair<b2Fixture*, b2Fixture*> > objCollTF;
    private:
        bool collisionRules(b2Fixture* fixtureA, b2Fixture* fixtureB);
        void insertCollision(b2Fixture* f1, b2Fixture* f2);
        
        
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        
    public:
        bool checkCollision(const std::string& name, const entity::TypeOfFixture type, b2Body*& bodyInCollison);
    };
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__CollisionListener__) */





