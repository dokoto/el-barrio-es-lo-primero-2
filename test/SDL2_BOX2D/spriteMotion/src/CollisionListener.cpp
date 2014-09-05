#include "CollisionListener.hpp"
#include <string>

#include "Sprite.hpp"
#include "Constants.hpp"
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
        
        objectsCollisioned.push_back(std::make_pair(contact->GetFixtureA(), contact->GetFixtureB()));
        
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Collision detected between %s and %s",
        // Sprite::getFixtureName(contact->GetFixtureA()).c_str(), Sprite::getFixtureName(contact->GetFixtureB().c_str());
        
        Sprite::TypeOfFixture f1 = utls::Fixture::getTypeOfFixture(contact->GetFixtureA());
        Sprite::TypeOfFixture f2 = utls::Fixture::getTypeOfFixture(contact->GetFixtureB());
        if (f1 == Sprite::TypeOfFixture::FIX_HORIZON && f2 == Sprite::TypeOfFixture::FIX_FOOT)
            contact->SetEnabled(true);
        else if (f1 == Sprite::TypeOfFixture::FIX_HORIZON && (f2 == Sprite::TypeOfFixture::FIX_ENEMY || f2 == Sprite::TypeOfFixture::FIX_CHARACTER))
            contact->SetEnabled(false);
        else if(f1 == Sprite::TypeOfFixture::FIX_CHARACTER && f2 == Sprite::TypeOfFixture::FIX_CHARACTER)
            contact->SetEnabled(false);
    }
    
    void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }
}