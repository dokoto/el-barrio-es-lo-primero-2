#include "Physics.hpp"

#include <sstream>

#include "ErrorsCodes.hpp"
#include "Conv.hpp"
#include "Names.hpp"
#include "Measures.hpp"
#include "Character.hpp"

namespace barrio {
    
    using namespace std;
    
    void Physics::CreateWorld(const b2Vec2 gravity, const Size<int>& screenSize)
    {
        world = new b2World{gravity};
        if (world != nullptr)
        {
            cartesianSize = utls::Conv::convSreenSizeToCartesianSize(screenSize);
            setWorldBundaries(measure::WORLD_WIDTH_PX, measure::WORLD_HEIGHT_PX);
            world->SetContactListener(&collisionPool);
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE,
                           "Physics World initialization with gravity[%2.2f, %2.2f]...OK", gravity.x, gravity.y);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics World initialization has failed.");
            throw error::PHYSICS_INIT_FAIL;
        }
        
    }
    
    
    void Physics::setFixtureCollisionFilters(b2FixtureDef& fixture, uint16 IAm,  uint16 ICollideWith)
    {
        fixture.filter.categoryBits = IAm;
        fixture.filter.maskBits = ICollideWith;
    }
    
    void Physics::setHorizon(void)
    {
        b2BodyDef groundDef;
        const char* name = name::HORIZON_NAME;
        groundDef.userData = (char*)name;
        b2Body* edge = world->CreateBody(&groundDef);
        b2Vec2 worldBundaries[11];
        size_t index = 0;
        b2Vec2 bb;
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {2, 475});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {206, 463});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {209, 491});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {324, 495});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {497, 463});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {526, 475});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {605, 454});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {602, 436});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {651, 420});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {1673, 595});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {1673, 590});
        worldBundaries[index++].Set(bb.x, bb.y);
        
        b2ChainShape chain;
        chain.CreateChain(worldBundaries, 11);
        edge->CreateFixture(&chain, 0.0f);
    }
    
    void Physics::setWorldBundaries(const int width, const int height)
    {
        b2BodyDef groundDef;
        const char* name = name::WORLD_BUNDARIES_NAME;
        groundDef.userData = (char*)name;
        b2Body* edge = world->CreateBody(&groundDef);
        b2Vec2 worldBundaries[5];
        b2Vec2 bb;
        
        worldBundaries[0].Set(0.0f, 0.0f);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {width, 0});
        worldBundaries[1].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {width, height});
        worldBundaries[2].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {0, height});
        worldBundaries[3].Set(bb.x, bb.y);
        
        bb =  utls::Conv::convScreenPosToCartesianPos(SDL_Point {0, 0});
        worldBundaries[4].Set(bb.x, bb.y);
        
        b2ChainShape chain;
        chain.CreateChain(worldBundaries, 5);
        edge->CreateFixture(&chain, 0.0f);
    }
    
    void Physics::createLine(const b2Vec2& pointA, const b2Vec2& pointB)
    {
        b2BodyDef rectBD;
        b2Body* rectB = world->CreateBody(&rectBD);
        
        b2EdgeShape shape;
        shape.Set(pointA, pointB);
        rectB->CreateFixture(&shape, 0.0f);
    }
    
    Physics::~Physics(void)
    {
        //Destroy physics
        if (world != nullptr)
        {
            delete world;
            world = nullptr;
            printf("Destroy Physics World...OK\n");
        }
    }
    
    bool Physics::bodyExist(const std::string& name)
    {
        if (!bodiesByName.empty())
        {
            map<string, b2Body*>::iterator it;
            it = bodiesByName.find(name);
            return  (it != bodiesByName.end()) ? true : false;
        }
        return false;
    }
    
    b2Body* Physics::addToWorld(const std::string& name, Sprite* sprite, const SDL_Point& screenPos,
                                const Size<int>& screenSize, const bool dynamicBody, const bool disableRotation)
    {
        if (sprite->getBody()->getTypeOfShape() == entity::TypeOfShape::SHP_POLYGON)
        {
            return createPolygon(name, sprite, screenPos, screenSize, dynamicBody, disableRotation);
        }
        else if (sprite->getBody()->getTypeOfShape() == entity::TypeOfShape::SHP_CIRCLE)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Type CIRCLES no supported yet : %s", name.c_str());
        }
        return nullptr;
    }
    
    b2Body* Physics::createPolygon(const std::string& name, Sprite* sprite, const SDL_Point& screenPos, const Size<int>& screenSize, const bool dynamicBody, const bool disableRotation)
    {
        if (bodyExist(name))
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Duplicate Physics body name : %s", name.c_str());
            throw error::PHYSICS_BODY_NAME_DUPLICATE;
        }
        
        Size<float32> cartesianSize = utls::Conv::convSreenSizeToCartesianSize(screenSize);
        b2Vec2 cartesianPos = utls::Conv::convScreenPosToCartesianPos(screenPos);
        
        b2BodyDef bodydef;
        bodydef.position.Set(cartesianPos.x, cartesianPos.y);
        bodydef.fixedRotation = disableRotation;
        
        if(dynamicBody == true)
        {
            bodydef.type=b2_dynamicBody;
            bodydef.userData = (void*) sprite->getBody();
        }
        else
        {
            bodydef.userData = (void*) sprite->getBody(name);
        }
        
        b2Body* body=world->CreateBody(&bodydef);
        
        b2PolygonShape shape;
        shape.SetAsBox(cartesianSize.w, cartesianSize.h);
        
        b2FixtureDef fixturedef;
        
        fixturedef.shape=&shape;
        fixturedef.density=1.0;
        fixturedef.userData = static_cast<void*>(sprite);
        body->CreateFixture(&fixturedef);
        bodiesByFixtureType.insert(make_pair(sprite->getBody()->getTypeOfFixture(), body));
        bodiesByName.insert(make_pair(name, body));
        bodiesByShapeType.insert(make_pair(sprite->getBody()->getTypeOfShape(), body));
        bodiesBySpriteType.insert(make_pair(sprite->getBody()->getTypeOfSprite(), body));
        
        if(dynamicBody == true)
        {
            shape.SetAsBox(cartesianSize.w, cartesianSize.h/90.0f, b2Vec2(0.0f, cartesianSize.h-cartesianSize.h/90.0f), 0.0f);
            if (sprite->getBody()->getTypeOfShape() == entity::TypeOfShape::SHP_POLYGON &&  sprite->getBody()->getTypeOfSprite() == entity::TypeOfSprite::SPRT_CHARACTER )
            {
                fixturedef.userData = (void*)sprite->getFoot();
                bodiesByFixtureType.insert(make_pair(sprite->getFoot()->getTypeOfFixture(), body));
            }
            else
                fixturedef.userData = nullptr;
            
            body->CreateFixture(&fixturedef);
            
            
            
            if (sprite->getBody()->getTypeOfFixture() == entity::TypeOfFixture::FIX_ENEMY)
            {
                
                Character* enemy = dynamic_cast<Character*>(sprite);
                if(enemy->getAIMode() == Glob::AIMode::AI_ATTACK)
                    enemiesInAttackMode.insert(std::make_pair(enemy->getBody()->getName(), body));
            }
        }
        
        return body;
    }
    
    
    b2Body* Physics::getBody(const std::string& spriteName)
    {
        map<string, b2Body*>::iterator it;
        it = bodiesByName.find(spriteName);
        if (it == bodiesByName.end())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No Physics body name: %s found", spriteName.c_str());
            throw error::PHYSICS_BODY_NAME_NOT_FOUND;
        }
        else
            return it->second;
        
        return nullptr;
        
    }    
    
}

