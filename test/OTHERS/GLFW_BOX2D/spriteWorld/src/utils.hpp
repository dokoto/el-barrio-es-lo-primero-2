#ifndef UTILS_HPP
#define UTILS_HPP

#include <Box2D/Box2D.h>
#include <string>
#include <cstring>
#include "types.hpp"

namespace utils {
    
    
    typeCollisionT checkTypeCollision(b2Fixture* fixtureA, b2Fixture* fixtureB );
    b2Body* getBodyBall(b2Fixture* fixtureA, b2Fixture* fixtureB );
    b2Body* getBodyGround(b2Fixture* fixtureA, b2Fixture* fixtureB );
    void setBallImpulse(objT LastHit, const b2Body* gnd, b2Body* ball);
    bool CheckHorizLoop(const b2Body* ball);
    bool CheckVertiLoop(const b2Body* ball);
    
    void CreateBullet(const b2Vec2 initPos, usrdata_t* bulletUD, b2World* lWorld);
    void CreateDirBullet(const b2Vec2 initPos, const b2Vec2 Vel, usrdata_t* bulletUD, b2World* lWorld);
    void CreateEnemyBall(const b2Vec2 initPos, const b2Vec2 initDir, const float32 radius, const float32 density,
                         const float32 restitution, const float32 friction,
                         const float32 gravity, usrdata_t* ballUD, b2World* lWorld);
    void CreateEnemyBox(const b2Vec2 initPos, const b2Vec2 initDir, const b2Vec2 size, const float32 density,
                        const float32 restitution, const float32 friction,
                        const float32 gravity, usrdata_t* boxUD, b2World* lWorld);
    
    void CreateRect(const b2Vec2 pointA, const b2Vec2 pointB, usrdata_t* rectUD, b2World* lWorld);
    void CreateBox(const float32 x, const float32 y, const float32 hx, const float32 hy, usrdata_t* boxUD, b2World* lWorld);
    void CreateDynBox(const float32 x, const float32 y, const float32 hx, const float32 hy, float32 friction, float32 density, float32 restitution,
                      usrdata_t* boxUD, b2World* lWorld);
    
    void CreatePlayer(const b2Vec2 initPos, const b2Vec2 initDir, const float32 radius, const float32 density,
                      const float32 restitution, const float32 friction,
                      const float32 gravity, usrdata_t* ballUD, b2World* lWorld);
    
    b2Body* getBody(const char* idtxt, b2World* lworld);
    void brakeShape(const char* idtxt, const b2Vec2 topVel, b2Body* shape);
    void getTypesInfo(const b2Fixture* fixtureA, const b2Fixture* fixtureB, int& typeA, int& typeB);
    void DestroyAllObjects(objects_t* vObj);
    void DestroyObject(const char* idtxt, objects_t* vObj);
    void AcctionsPostCollision(CollisionedObjects_t& CollisionedObjects, objects_t* mObjs, b2World* lWorld);
    inline usrdata_t* CreateUD(usrdata_t* UD, objects_t* vObj)
    {
        vObj->insert(std::make_pair(UD->idtxt, UD));
        return UD;
    }
    
    #define CUD(IDTXT, TYPE, SHAPE, VECTOR) utils::CreateUD(new usrdata_t(IDTXT, TYPE, SHAPE), VECTOR)
    
}

#endif // UTILS_HPP
