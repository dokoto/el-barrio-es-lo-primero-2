#include "CollisionListener.hpp"
#include <string>

#include "Sprite.hpp"
#include "Fixture.hpp"

namespace barrio {
    using namespace std;
    
    void CollisionListener::BeginContact(b2Contact* contact)
    {
        B2_NOT_USED(contact);
    }
    
    void CollisionListener::EndContact(b2Contact* contact)
    {
        B2_NOT_USED(contact);
    }
    
    void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
        B2_NOT_USED(oldManifold);
        if (contact->GetManifold()->pointCount == 0) return;
        
        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();
        
        objectsCollisionedByNameVSTypeOfFixture.insert(std::make_pair(utls::Fixture::getFixtureName(f1), utls::Fixture::getTypeOfFixture(f2)));
        
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Collision detected between %s and %s",
                utls::Fixture::getFixtureName(f1).c_str(), utls::Fixture::getFixtureName(f2).c_str());
        contact->SetEnabled(collisionRules(contact->GetFixtureA(), contact->GetFixtureB()));
   
    }
    
    bool CollisionListener::collisionRules(b2Fixture* fixtureA, b2Fixture* fixtureB)
    {
        entity::TypeOfFixture f1 = utls::Fixture::getTypeOfFixture(fixtureA);
        entity::TypeOfFixture f2 = utls::Fixture::getTypeOfFixture(fixtureB);
        
        if ( (f1 == entity::TypeOfFixture::FIX_HORIZON && f2 == entity::TypeOfFixture::FIX_FOOT) ||
             (f1 == entity::TypeOfFixture::FIX_FOOT && f2 == entity::TypeOfFixture::FIX_HORIZON) ||
             (f1 == entity::TypeOfFixture::FIX_WORLD_BUDARIES && f2 == entity::TypeOfFixture::FIX_FOOT) ||
             (f1 == entity::TypeOfFixture::FIX_FOOT && f2 == entity::TypeOfFixture::FIX_WORLD_BUDARIES) ||
             (f1 == entity::TypeOfFixture::FIX_WORLD_BUDARIES && f2 == entity::TypeOfFixture::FIX_CHARACTER) ||
             (f1 == entity::TypeOfFixture::FIX_CHARACTER && f2 == entity::TypeOfFixture::FIX_WORLD_BUDARIES) ||
             (f1 == entity::TypeOfFixture::FIX_FURNITURE && f2 == entity::TypeOfFixture::FIX_WORLD_BUDARIES) ||
             (f1 == entity::TypeOfFixture::FIX_WORLD_BUDARIES && f2 == entity::TypeOfFixture::FIX_FURNITURE) ||
             (f1 == entity::TypeOfFixture::FIX_CHARACTER && f2 == entity::TypeOfFixture::FIX_FURNITURE) )
        {
            return true;
        }
        else if ( (f1 == entity::TypeOfFixture::FIX_HORIZON && f2 == entity::TypeOfFixture::FIX_ENEMY) ||
                  (f1 == entity::TypeOfFixture::FIX_ENEMY && f2 == entity::TypeOfFixture::FIX_HORIZON) ||
                  (f1 == entity::TypeOfFixture::FIX_HORIZON && f2 == entity::TypeOfFixture::FIX_CHARACTER) ||
                  (f1 == entity::TypeOfFixture::FIX_CHARACTER && f2 == entity::TypeOfFixture::FIX_HORIZON) ||
                  (f1 == entity::TypeOfFixture::FIX_FOOT && f2 == entity::TypeOfFixture::FIX_CHARACTER) ||
                  (f1 == entity::TypeOfFixture::FIX_CHARACTER && f2 == entity::TypeOfFixture::FIX_FOOT) ||
                  (f1 == entity::TypeOfFixture::FIX_CHARACTER && f2 == entity::TypeOfFixture::FIX_CHARACTER) )
        {
            return false;
        }
        else
            return false;
    }
    
    void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }
}