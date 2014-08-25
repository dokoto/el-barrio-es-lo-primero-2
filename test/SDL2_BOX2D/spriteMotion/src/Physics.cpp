#include "Physics.hpp"
#include "errorsCodes.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

namespace barrio {
    
    using namespace std;
    
    void Physics::CreateWorld(const b2Vec2 gravity, const Size<int>& screenSize)
    {
        world = new b2World{gravity};
        if (world != nullptr)
        {
            cartesianSize = Utils::convSreenSizeToCartesianSize(screenSize);
            setWorldBundaries(consts::WORLD_WIDTH_PX, consts::WORLD_HEIGHT_PX);
            //world->SetContactListener(&collisionPool);
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE,
                           "Physics World initialization with gravity[%f/%f]...OK", gravity.x, gravity.y);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics World initialization has failed.");
            throw error::PHYSICS_INIT_FAIL;
        }
        
    }
    
    void Physics::setWorldBundaries(const int width, const int height)
    {
        b2BodyDef groundDef;
        b2Body* edge = world->CreateBody(&groundDef);
        b2Vec2 worldBundaries[5];
        b2Vec2 bb;
        
        worldBundaries[0].Set(0.0f, 0.0f);
        
        bb =  Utils::convScreenPosToCartesianPos(SDL_Point {width, 0});
        worldBundaries[1].Set(bb.x, bb.y);
        
        bb =  Utils::convScreenPosToCartesianPos(SDL_Point {width, height});
        worldBundaries[2].Set(bb.x, bb.y);
        
        bb =  Utils::convScreenPosToCartesianPos(SDL_Point {0, height});
        worldBundaries[3].Set(bb.x, bb.y);
        
        bb =  Utils::convScreenPosToCartesianPos(SDL_Point {0, 0});
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
    
    void Physics::addToWorld(const std::string& name, Sprite* sprite, const SDL_Point& screenPos,
                             const Size<int>& screenSize, const bool dynamicBody, const bool disableRotation)
    {
        if (sprite->getTypeOfShape() == Sprite::TypeOfShape::POLYGON)
        {
            createPolygon(name, sprite, screenPos, screenSize, dynamicBody, disableRotation);
        }
        else if (sprite->getTypeOfShape() == Sprite::TypeOfShape::CIRCLE)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Type CIRCLES no supported yet : %s", name.c_str());
        }
    }
    
    
    void Physics::createPolygon(const std::string& name, Sprite* sprite, const SDL_Point& screenPos, const Size<int>& screenSize, const bool dynamicBody, const bool disableRotation)
    {     
        if (bodyExist(name))
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Duplicate Physics body name : %s", name.c_str());
            throw error::PHYSICS_BODY_NAME_DUPLICATE;
        }
        
        Size<float32> cartesianSize = Utils::convSreenSizeToCartesianSize(screenSize);
        b2Vec2 cartesianPos = Utils::convScreenPosToCartesianPos(screenPos);
        
        b2BodyDef bodydef;
        bodydef.position.Set(cartesianPos.x, cartesianPos.y);
        bodydef.fixedRotation = disableRotation;
        bodydef.userData = static_cast<void*>(sprite);
        if(dynamicBody == true)
            bodydef.type=b2_dynamicBody;
        
        b2Body* body=world->CreateBody(&bodydef);
        
        b2PolygonShape shape;
        shape.SetAsBox(cartesianSize.w, cartesianSize.w);
        
        b2FixtureDef fixturedef;
        fixturedef.shape=&shape;
        fixturedef.density=1.0;
        body->CreateFixture(&fixturedef);
        
        bodiesByName.insert(make_pair(name, body));
        bodiesByShapeType.insert(make_pair(sprite->getTypeOfShape(), body));
        bodiesBySpriteType.insert(make_pair(sprite->getTypeOfSprite(), body));
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

