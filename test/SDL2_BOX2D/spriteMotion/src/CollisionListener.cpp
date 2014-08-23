#include "CollisionListener.hpp"

namespace barrio {
    
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
        const b2Body* b1 = contact->GetFixtureA()->GetBody();
        const b2Body* b2 = contact->GetFixtureB()->GetBody();
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Collision detected Fx1[%f, %f] Fx2[%f, %f]", b1->GetPosition().x, b1->GetPosition().y,
                       b2->GetPosition().x, b2->GetPosition().y);
    }
    
    void CollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }
}