#include "Physics.hpp"
#include "errorsCodes.hpp"



namespace barrio {
    
    using namespace std;
    
    void Physics::CreateWorld(const b2Vec2 gravity, const float32 cartesianWidth, const float32 cartesianHeight)
    {
        world = new b2World{gravity};
        if (world != nullptr)
        {
            this->cartesianWidth = cartesianWidth;
            this->cartesianHeight = cartesianHeight;
            definePhysicsWorldBundaries();
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE,
                           "Physics World initialization with gravity[%f/%f]...OK", gravity.x, gravity.y);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Physics World initialization has failed.");
            throw error::PHYSICS_INIT_FAIL;
        }
        
    }
    
    void Physics::definePhysicsWorldBundaries()
    {
        float32 x = cartesianWidth / 2;
        float32 x_minus = -x;
        float32 y = cartesianHeight / 2;
        float32 y_minus = -y;
        
        // Linea horizontal superior
        createLine(b2Vec2{x_minus, y}, b2Vec2{x, y});
        // Linea vertical derecha
        createLine(b2Vec2{x, y}, b2Vec2{x, y_minus});
        // Linea horizontal inferior
        createLine(b2Vec2{x, y_minus}, b2Vec2{x_minus, y_minus});
        // Linea vertical izquierda
        createLine(b2Vec2{x_minus, y_minus}, b2Vec2{x_minus, y});
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
    
    void Physics::createLine(const b2Vec2& pointA, const b2Vec2& pointB)
    {
        b2BodyDef rectBD;
        b2Body* rectB = world->CreateBody(&rectBD);
        
        b2EdgeShape shape;
        shape.Set(pointA, pointB);
        rectB->CreateFixture(&shape, 0.0f);
    }
    
    bool Physics::bodyExist(const std::string& name)
    {
        if (!bodies.empty())
        {
            map<string, b2Body*>::iterator it;
            it = bodies.find(name);
            return  (it != bodies.end()) ? true : false;
        }
        return false;
    }
    
    void Physics::createPolygon(const std::string& spriteName, const float spriteWidth, const float spriteHeight, const b2Vec2& spritePosition)
    {
     
        if (bodyExist(spriteName))
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Duplicate Physics body name : %s", spriteName.c_str());
            throw error::PHYSICS_BODY_NAME_DUPLICATE;
        }
        
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(spritePosition.x, spritePosition.y);
        b2Body* body = world->CreateBody(&bodyDef);
        
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(spriteWidth, spriteHeight);
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        
        body->CreateFixture(&fixtureDef);
        
        bodies.insert(make_pair(spriteName, body));
    }
    
    b2Body* Physics::getBody(const std::string& spriteName)
    {
        map<string, b2Body*>::iterator it;
        it = bodies.find(spriteName);
        if (it == bodies.end())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No Physics body name: %s found", spriteName.c_str());
            throw error::PHYSICS_BODY_NAME_NOT_FOUND;
        }
        else
            return it->second;
        
        return nullptr;
        
    }        
}

