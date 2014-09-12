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
        
        insertCollision(f1, f2);
        contact->SetEnabled(collisionRules(contact->GetFixtureA(), contact->GetFixtureB()));
        /*
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Collision detected between %s and %s",
                       utls::Fixture::getFixtureName(f1).c_str(), utls::Fixture::getFixtureName(f2).c_str());
         */
    }
    
    bool CollisionListener::checkCollision(const std::string& name, const entity::TypeOfFixture type, b2Body*& bodyInCollison)
    {
        auto it = objCollTF.find(make_pair(name, type));
        if (it != objCollTF.end())
        {
            bodyInCollison = it->second.second->GetBody();
            objCollTF.erase(it);
            return true;
        }
        else
            return false;
    }
    
    void CollisionListener::insertCollision(b2Fixture* f1, b2Fixture* f2)
    {
        objCollTF.insert(make_pair(make_pair(utls::Fixture::getFixtureName(f1), utls::Fixture::getTypeOfFixture(f2)), make_pair(f1, f2)));
    }
    
    bool CollisionListener::collisionRules(b2Fixture* fixtureA, b2Fixture* fixtureB)
    {
        entity::TypeOfFixture f1 = utls::Fixture::getTypeOfFixture(fixtureA);
        entity::TypeOfFixture f2 = utls::Fixture::getTypeOfFixture(fixtureB);
        
        if ( (f1 == entity::FIX_HORIZON && f2 == entity::FIX_CHARACTER_FOOT) ||
             (f1 == entity::FIX_HORIZON && f2 == entity::FIX_ENEMY_FOOT) ||
             (f1 == entity::FIX_CHARACTER_FOOT && f2 == entity::FIX_HORIZON) ||
             (f1 == entity::FIX_ENEMY_FOOT && f2 == entity::FIX_HORIZON) ||
             (f1 == entity::FIX_WORLD_BUDARIES && f2 == entity::FIX_CHARACTER_FOOT) ||
             (f1 == entity::FIX_WORLD_BUDARIES && f2 == entity::FIX_ENEMY_FOOT) ||
             (f1 == entity::FIX_CHARACTER_FOOT && f2 == entity::FIX_WORLD_BUDARIES) ||
             (f1 == entity::FIX_ENEMY_FOOT && f2 == entity::FIX_WORLD_BUDARIES) ||
             (f1 == entity::FIX_WORLD_BUDARIES && f2 == entity::FIX_CHARACTER) ||
             (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_WORLD_BUDARIES) ||
             (f1 == entity::FIX_FURNITURE && f2 == entity::FIX_WORLD_BUDARIES) ||
             (f1 == entity::FIX_WORLD_BUDARIES && f2 == entity::FIX_FURNITURE) ||
             (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_FURNITURE) )
        {
            return true;
        }
        else if ( (f1 == entity::FIX_HORIZON && f2 == entity::FIX_ENEMY) ||
                  (f1 == entity::FIX_ENEMY && f2 == entity::FIX_HORIZON) ||
                  (f1 == entity::FIX_HORIZON && f2 == entity::FIX_CHARACTER) ||
                  (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_HORIZON) ||
                  (f1 == entity::FIX_ENEMY_FOOT && f2 == entity::FIX_CHARACTER) ||
                  (f1 == entity::FIX_CHARACTER_FOOT && f2 == entity::FIX_CHARACTER) ||
                  (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_ENEMY_FOOT) ||
                 (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_ENEMY_FOOT) ||
                  (f1 == entity::FIX_CHARACTER && f2 == entity::FIX_CHARACTER) )
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