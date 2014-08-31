#include "CollisionListener.hpp"
#include "Sprite.hpp"
#include "Constants.hpp"
#include <string>

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
        ObjectsCollisioned.push_back(std::make_pair(contact->GetFixtureA(), contact->GetFixtureB()));
        string b1Name = Sprite::getFixtureName(contact->GetFixtureA());
        string b2Name = Sprite::getFixtureName(contact->GetFixtureB());
        
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Collision detected between %s and %s", b1Name.c_str(), b2Name.c_str());
        
        Sprite::typeOfFixture f1 = Sprite::getFixtureTypeOfFixture(contact->GetFixtureA());
        Sprite::typeOfFixture f2 = Sprite::getFixtureTypeOfFixture(contact->GetFixtureB());
        if (f1 == Sprite::typeOfFixture::FIX_HORIZON && f2 == Sprite::typeOfFixture::FIX_FOOT)
            contact->SetEnabled(true);
        else if (f1 == Sprite::typeOfFixture::FIX_HORIZON && (f2 == Sprite::typeOfFixture::FIX_ENEMY || f2 == Sprite::typeOfFixture::FIX_CHARACTER))
            contact->SetEnabled(false);
        
    }
    
    void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }
}