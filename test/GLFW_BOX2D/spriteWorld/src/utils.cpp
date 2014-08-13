#include "utils.hpp"

namespace utils {
    
    
    typeCollisionT checkTypeCollision(b2Fixture* fixtureA, b2Fixture* fixtureB )
    {
#define SI(TA, TB) (typeA == TA && typeB == TB) || (typeB == TA && typeA == TB)
        int typeA, typeB;
        getTypesInfo(fixtureA, fixtureB, typeA, typeB);
        
        if (typeA == OBJT_NULL || typeB == OBJT_NULL)
            return TYPECOLLISIONT_NULL;
        
        if ( SI(CIRCLE_ENEMY, GND_DOWN) )
            return CIRCLE_ENEMY_vs_GROND;
        
        if ( SI(CIRCLE_ENEMY, BULLET) )
            return CIRCLE_ENEMY_vs_BULLET;
        
        if ( SI(CIRCLE_ENEMY, DYNBOX) )
            return CIRCLE_ENEMY_vs_HERO;
        
        if ( SI(BOX_ENEMY, DYNBOX) )
            return BOX_ENEMY_vs_BULLET;
        
        // DEBE ESTAR SIEMPRE EL ULTIMO !!
        if (typeA == BULLET || typeB == BULLET)
            return ANY_vs_BULLET;
        
        return TYPECOLLISIONT_NULL;
    }
    
    void getTypesInfo(const b2Fixture* fixtureA, const b2Fixture* fixtureB, int& typeA, int& typeB)
    {
        const b2Body* b1 = fixtureA->GetBody();
        usrdata_t* usr1 = static_cast<usrdata_t*>(b1->GetUserData());
        const b2Body* b2 = fixtureB->GetBody();
        usrdata_t* usr2 = static_cast<usrdata_t*>(b2->GetUserData());
        typeA = (usr1 != NULL) ? usr1->type : OBJT_NULL;
        typeB = (usr2 != NULL) ? usr2->type : OBJT_NULL;
        
    }
    
    b2Body* getBodyBall(b2Fixture* fixtureA, b2Fixture* fixtureB )
    {
        b2Body* b1 = fixtureA->GetBody();
        usrdata_t* usr1 = static_cast<usrdata_t*>(b1->GetUserData());
        if (usr1->type == CIRCLE_ENEMY) return b1;
        b2Body* b2 = fixtureB->GetBody();
        usrdata_t* usr2 = static_cast<usrdata_t*>(b2->GetUserData());
        if (usr2->type == CIRCLE_ENEMY) return b2;
        
        return NULL;
    }
    
    
    
    b2Body* getBodyGround(b2Fixture* fixtureA, b2Fixture* fixtureB )
    {
        b2Body* b1 = fixtureA->GetBody();
        usrdata_t* usr1 = static_cast<usrdata_t*>(b1->GetUserData());
        if (usr1 == NULL) return NULL;
        if (usr1->type >= GND_UP && usr1->type <= GND_LEFT) return b1;
        b2Body* b2 = fixtureB->GetBody();
        usrdata_t* usr2 = static_cast<usrdata_t*>(b2->GetUserData());
        if (usr2 == NULL) return NULL;
        if (usr2->type >= GND_UP && usr2->type <= GND_LEFT) return b2;
        
        return NULL;
    }
    
    void setBallImpulse(objT LastHit, const b2Body* gnd, b2Body* ball)
    {
        
        objT currentHit = static_cast<usrdata_t*>(gnd->GetUserData())->type;
        b2Vec2 vel = ball->GetLinearVelocity();
        if (abs(vel.x) > 1.0f || abs(vel.y) > 1.0f)
            ball->SetLinearVelocity(b2Vec2(0.05f, 0.05f));
        
        if (CheckVertiLoop(ball))
        {
            ball->ApplyForceToCenter(b2Vec2(-0.05f, 0.05f), false);
            return;
        }
        
        if (CheckHorizLoop(ball))
        {
            ball->ApplyForceToCenter(b2Vec2(0.05f, -0.05f), false);
            return;
        }
        
        if (LastHit == GND_LEFT && currentHit == GND_DOWN)
            ball->ApplyForceToCenter(b2Vec2(0.05f, 0.05f), false);
        else if (LastHit == GND_RIGHT && currentHit == GND_DOWN)
            ball->ApplyForceToCenter(b2Vec2(-0.05f, 0.05f), false);
        
        else if (LastHit == GND_LEFT && currentHit == GND_UP)
            ball->ApplyForceToCenter(b2Vec2(0.05f, -0.05f), false);
        else if (LastHit == GND_RIGHT && currentHit == GND_UP)
            ball->ApplyForceToCenter(b2Vec2(-0.05f, 0.05f), false);
        
        else if (LastHit == GND_UP && currentHit == GND_RIGHT)
            ball->ApplyForceToCenter(b2Vec2(-0.05f, -0.05f), false);
        else if (LastHit == GND_DOWN && currentHit == GND_RIGHT)
            ball->ApplyForceToCenter(b2Vec2(-0.05f, 0.05f), false);
        
        else if (LastHit == GND_UP && currentHit == GND_LEFT)
            ball->ApplyForceToCenter(b2Vec2(0.05f, -0.05f), false);
        else if (LastHit == GND_DOWN && currentHit == GND_LEFT)
            ball->ApplyForceToCenter(b2Vec2(0.05f, 0.05f), false);
        
    }
    
    bool CheckHorizLoop(const b2Body* ball)
    {
        const size_t itera = 2;
        static size_t indLoop = 0;
        static float32 HorizLoop[itera];
        memset(HorizLoop, 0, sizeof(HorizLoop[0]) *itera);
        const b2Vec2 pos = ball->GetPosition();
        HorizLoop[indLoop++] = abs(pos.x);
        float32 sum = 0;
        for(size_t i = 0; i < itera; i++) sum += HorizLoop[i];
        if ( ( HorizLoop[0] * itera ) == sum )
        {
            indLoop = 0;
            return true;
        }
        if (indLoop == 5) indLoop = 0;
        return false;
        
    }
    
    bool CheckVertiLoop(const b2Body* ball)
    {
        const size_t itera = 2;
        static size_t indLoop = 0;
        static float32 vertLoop[itera];
        memset(vertLoop, 0, sizeof(vertLoop[0]) *itera);
        const b2Vec2 pos = ball->GetPosition();
        vertLoop[indLoop++] = abs(pos.y);
        float32 sum = 0;
        for(size_t i = 0; i < itera; i++) sum += vertLoop[i];
        if ( ( vertLoop[0] * itera ) == sum )
        {
            indLoop = 0;
            return true;
        }
        if (indLoop == 5) indLoop = 0;
        
        return false;
        
    }
    
    void CreatePlayer(const b2Vec2 initPos, const b2Vec2 initDir, const float32 radius, const float32 density,
                      const float32 restitution, const float32 friction,
                      const float32 gravity, usrdata_t* ballUD, b2World* lWorld)
    {
        
        b2CircleShape shapeC;
        shapeC.m_radius = radius;
        
        b2FixtureDef fd;
        fd.shape = &shapeC;
        fd.density = density;
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(initPos.x, initPos.y);
        bd.userData = static_cast<void*>(ballUD);
        
        b2Body* circle = lWorld->CreateBody(&bd);
        
        fd.restitution = restitution;
        fd.friction = friction;
        circle->CreateFixture(&fd);
        if (gravity != 0.0f)
            circle->SetGravityScale(gravity);
        
    }
    
    void CreateDynBox(const float32 x, const float32 y, const float32 hx, const float32 hy, float32 friction, float32 density, float32 restitution,
                      usrdata_t* boxUD, b2World* lWorld)
    {
        b2PolygonShape shapeR;
        shapeR.SetAsBox(hx, hy);
        
        b2FixtureDef fdR;
        fdR.shape = &shapeR;
        fdR.density = density;
        fdR.friction = friction;
        fdR.restitution = restitution;
        
        b2BodyDef bdR;
        bdR.type = b2_dynamicBody;
        bdR.position.Set(x, y);
        
        bdR.userData = static_cast<void*>(boxUD);
        
        b2Body* bodyR = lWorld->CreateBody(&bdR);
        bodyR->CreateFixture(&fdR);
    }
    
    void CreateBox(const float32 x, const float32 y, const float32 hx, const float32 hy, usrdata_t* boxUD, b2World* lWorld)
    {
        b2PolygonShape shapeR;
        shapeR.SetAsBox(hx, hy);
        
        b2FixtureDef fdR;
        fdR.shape = &shapeR;
        fdR.density = 1.0f;
        
        b2BodyDef bdR;
        bdR.type = b2_staticBody;
        bdR.position.Set(x, y);
        bdR.userData = static_cast<void*>(boxUD);
        
        b2Body* bodyR = lWorld->CreateBody(&bdR);
        bodyR->CreateFixture(&fdR);
    }
    
    
    void CreateRect(const b2Vec2 pointA, const b2Vec2 pointB, usrdata_t* rectUD, b2World* lWorld)
    {
        b2BodyDef rectBD;
        rectBD.userData = static_cast<void*>(rectUD);
        b2Body* rectB = lWorld->CreateBody(&rectBD);
        
        b2EdgeShape shape;
        shape.Set(pointA, pointB);
        rectB->CreateFixture(&shape, 0.0f);
    }
    
    void CreateEnemyBall(const b2Vec2 initPos, const b2Vec2 initDir, const float32 radius, const float32 density,
                         const float32 restitution, const float32 friction,
                         const float32 gravity, usrdata_t* ballUD, b2World* lWorld)
    {
        b2CircleShape shapeC;
        shapeC.m_radius = radius;
        
        b2FixtureDef fd;
        fd.shape = &shapeC;
        fd.density = density;
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(initPos.x, initPos.y);
        bd.userData = static_cast<void*>(ballUD);
        
        b2Body* circle = lWorld->CreateBody(&bd);
        
        fd.restitution = restitution;
        fd.friction = friction;
        circle->CreateFixture(&fd);
        if (gravity != 0.0f)
            circle->SetGravityScale(gravity);
        circle->ApplyForceToCenter(initDir, false);
    }
    
    void CreateEnemyBox(const b2Vec2 initPos, const b2Vec2 initDir, const b2Vec2 size, const float32 density,
                        const float32 restitution, const float32 friction,
                        const float32 gravity, usrdata_t* boxUD, b2World* lWorld)
    {
        b2PolygonShape shapeR;
        shapeR.SetAsBox(size.x, size.y);
        
        b2FixtureDef fd;
        fd.shape = &shapeR;
        fd.density = density;
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(initPos.x, initPos.y);
        bd.userData = static_cast<void*>(boxUD);
        
        b2Body* box = lWorld->CreateBody(&bd);
        
        fd.restitution = restitution;
        fd.friction = friction;
        box->CreateFixture(&fd);
        if (gravity != 0.0f)
            box->SetGravityScale(gravity);
        box->ApplyForceToCenter(initDir, false);
    }
    
    void CreateBullet(const b2Vec2 initPos, usrdata_t* bulletUD, b2World* lWorld)
    {
        b2CircleShape shape;
        shape.m_radius = 0.25f;
        
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;
        fd.restitution = 0.05f;
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.bullet = true;
        bd.position.Set(initPos.x, initPos.y);
        bd.userData = static_cast<void*>(bulletUD);
        
        b2Body* m_bullet = lWorld->CreateBody(&bd);
        m_bullet->CreateFixture(&fd);
        
        m_bullet->SetLinearVelocity(b2Vec2(0.0f, 400.0f));
    }
    
    void CreateDirBullet(const b2Vec2 initPos, const b2Vec2 Vel, usrdata_t* bulletUD, b2World* lWorld)
    {
        b2CircleShape shape;
        shape.m_radius = 0.25f;
        
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;
        fd.restitution = 0.05f;
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.bullet = true;
        bd.position.Set(initPos.x, initPos.y);
        bd.userData = static_cast<void*>(bulletUD);
        
        b2Body* m_bullet = lWorld->CreateBody(&bd);
        m_bullet->CreateFixture(&fd);
        
        m_bullet->SetLinearVelocity(Vel);
    }
    
    
    b2Body* getBody(const char* idtxt, b2World* lworld)
    {
        for(b2Body* b = lworld->GetBodyList(); b; b = b->GetNext())
        {
            usrdata_t* usr = static_cast<usrdata_t*>(b->GetUserData());
            if (usr == NULL) continue;
            if (usr->type < CIRCLE_ENEMY || usr->type > OBJT_NULL) continue;
            if (usr->idtxt.compare(idtxt) == 0)
                return b;
        }
        return NULL;
    }
    
    void brakeShape(const char* idtxt, const b2Vec2 topVel, b2Body* shape)
    {
        usrdata_t* usr = static_cast<usrdata_t*>(shape->GetUserData());
        if (usr->idtxt.compare(idtxt) == 0)
        {
            b2Vec2 vel = shape->GetLinearVelocity();
            if (abs(vel.x) > topVel.x || abs(vel.y) > topVel.y)
            {
                shape->SetLinearVelocity(b2Vec2(vel.x/2, vel.y/2));
            }
        }
    }
    
    void DestroyAllObjects(objects_t* vObj)
    {
        for (objects_t::iterator it = vObj->begin(); it != vObj->end(); it++)
        {
            usrdata_t* usr = it->second;
            if (usr->type == CIRCLE_ENEMY)
            {
                enemy_t* obj = static_cast<enemy_t*>(usr->object);
                delete obj;
            }
            delete it->second;
        }
        vObj->clear();
    }
    
    void DestroyObject(const char* idtxt, objects_t* vObj)
    {
        objects_t::iterator it = vObj->find(idtxt);
        if (it != vObj->end())
        {
            usrdata_t* usr = it->second;
            enemy_t* obj = static_cast<enemy_t*>(usr->object);
            delete obj;
            vObj->erase(it);
        }
    }
    
    void AcctionsPostCollision(CollisionedObjects_t& CollisionedObjects, objects_t* mObjs, b2World* lWorld)
    {
        for (CollisionedObjects_t::iterator it = CollisionedObjects.begin();
             it != CollisionedObjects.end();
             it++)
        {
            if (checkTypeCollision(it->first, it->second) == CIRCLE_ENEMY_vs_GROND)
            {
                b2Body* ground = getBodyGround(it->first, it->second);
                if (ground == NULL) return;
                b2Body* ball = getBodyBall(it->first, it->second);
                if (ball == NULL) return;
                usrdata_t* usrG = static_cast<usrdata_t*>(ground->GetUserData());
                usrdata_t* usr = static_cast<usrdata_t*>(ball->GetUserData());
                enemy_t* enemy = static_cast<enemy_t*>(usr->object);
                if (enemy->size == 1  && usrG->type == GND_DOWN)
                {
                    b2Vec2 pos = ball->GetLinearVelocity();
                    pos.x = (pos.x > 0) ? 5.0f : -5.0f;
                    pos.y = (pos.y > 0) ? 10.0f : -10.0f;
                    ball->SetLinearVelocity(pos);
                }
                else if (enemy->size == 2 && usrG->type == GND_DOWN)
                {
                    b2Vec2 pos = ball->GetLinearVelocity();
                    pos.x = (pos.x > 0) ? 5.0f : -5.0f;
                    pos.y = (pos.y > 0) ? 15.0f : -15.0f;
                    ball->SetLinearVelocity(pos);
                }
                else if (enemy->size == 3  && usrG->type == GND_DOWN)
                {
                    b2Vec2 pos = ball->GetLinearVelocity();
                    pos.x = (pos.x > 0) ? 5.0f : -5.0f;
                    pos.y = (pos.y > 0) ? 20.0f : -20.0f;
                    ball->SetLinearVelocity(pos);
                }
                else if (enemy->size == 4  && usrG->type == GND_DOWN)
                {
                    b2Vec2 pos = ball->GetLinearVelocity();
                    pos.x = (pos.x > 0) ? 5.0f : -5.0f;
                    pos.y = (pos.y > 0) ? 25.0f : -25.0f;
                    ball->SetLinearVelocity(pos);
                }
            }
            else if (checkTypeCollision(it->first, it->second) == CIRCLE_ENEMY_vs_BULLET)
            {
                b2Body* bullet = getBody("bullet", lWorld);
                if (bullet != NULL)
                    lWorld->DestroyBody(bullet);
                b2Body* ball = getBodyBall(it->first, it->second);
                if (ball == NULL) return;
                usrdata_t* usr = static_cast<usrdata_t*>(ball->GetUserData());
                enemy_t* enemy = static_cast<enemy_t*>(usr->object);
                enemy_t* ballA = NULL, *ballB = NULL;
                enemy->SplitBall(ballA, ballB);
                char buff[30];
                static size_t iid = 0;
                if (ballA != NULL && ballB != NULL)
                {
                    
                    float32 velX = 505.0f;
                    float32 velY = -0.5f;
                    float posX = ball->GetPosition().x;
                    float posY = ball->GetPosition().y;
                    
                    sprintf(buff, "splitBall_%ld", iid++);
                    CreateEnemyBall(b2Vec2(posX-ballA->radius, posY), b2Vec2(velX*-1, velY), ballA->radius, 1.0f, 1.0f, 0.0f, 0.0f,
                                    CUD(buff, CIRCLE_ENEMY, ballA, mObjs), lWorld);
                    
                    sprintf(buff, "splitBall_%ld", iid++);
                    CreateEnemyBall(b2Vec2(posX+ballB->radius, posY), b2Vec2(velX, velY), ballB->radius, 1.0f, 1.0f, 0.0f, 0.0f,
                                    CUD(buff, CIRCLE_ENEMY, ballB, mObjs), lWorld);
                    
                }
                DestroyObject(usr->idtxt.c_str(), mObjs);
                lWorld->DestroyBody(ball);
                
            }
            else if (checkTypeCollision(it->first, it->second) == BOX_ENEMY_vs_BULLET)
            {
                
            }
            else if (checkTypeCollision(it->first, it->second) == ANY_vs_BULLET)
            {
                b2Body* bullet = getBody("bullet", lWorld);
                if (bullet != NULL)
                    lWorld->DestroyBody(bullet);
            }
            else if (checkTypeCollision(it->first, it->second) == CIRCLE_ENEMY_vs_HERO)
            {            
                b2Body* hero = getBody("hero", lWorld);
                if (hero == NULL) return;
                usrdata_t* usr = static_cast<usrdata_t*>(hero->GetUserData());
                enemy_t* enemy = static_cast<enemy_t*>(usr->object);
                enemy->gameover = true;
            }
            
        }
        if (!CollisionedObjects.empty())
        {
            CollisionedObjects.clear();
        }
    }
}


