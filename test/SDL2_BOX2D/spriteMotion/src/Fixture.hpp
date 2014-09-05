#ifndef EL_BARRIO_ES_LO_PRIMERO_Fixtures_h
#define EL_BARRIO_ES_LO_PRIMERO_Fixtures_h

namespace barrio
{
    namespace utls
    {
        class Fixture
        {
        public:
            
            static Object::TypeOfSprite getTypeOfSprite(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                        return  sprite->getTypeOfSprite();
                    else
                        return Object::TypeOfSprite::SPRT_NONE;
                    
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Circle no implemented");
                    return Object::TypeOfSprite::SPRT_NONE;
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    return Object::TypeOfSprite::SPRT_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Shape no implemented");
                    return Object::TypeOfSprite::SPRT_NONE;
                }
            }
            
            static Object::TypeOfShape getTypeOfShape(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                        return  sprite->getTypeOfShape();
                    else
                        return Object::TypeOfShape::SHP_POLYGON;
                    
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    return Object::TypeOfShape::SHP_CIRCLE;
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    return Object::TypeOfShape::SHP_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfShape: Shape no implemented");
                    return Object::TypeOfShape::SHP_NONE;
                }
            }
            
            static Object::TypeOfFixture getTypeOfFixture(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                    {
                        std::string name = getFixtureName(fixture);
                        if(name.find(consts::FOOT_NAME) != std::string::npos)
                            return Object::TypeOfFixture::FIX_FOOT;
                        else if (sprite->getTypeOfSprite() == Object::TypeOfSprite::SPRT_CHARACTER)
                            return Object::TypeOfFixture::FIX_CHARACTER;
                        else if (sprite->getTypeOfSprite() == Object::TypeOfSprite::SPRT_ENEMY)
                            return Object::TypeOfFixture::FIX_ENEMY;
                        else if (sprite->getTypeOfSprite() == Object::TypeOfSprite::SPRT_FURNITURE)
                            return Object::TypeOfFixture::FIX_FURNITURE;
                        else
                            return Object::TypeOfFixture::FIX_NONE;
                        
                    }
                    else
                        return Object::TypeOfFixture::FIX_NONE;
                    
                }
                else if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Circle no implemented");
                    return Object::TypeOfFixture::FIX_NONE;
                }
                else if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    std::string name = getFixtureName(fixture);
                    if (name.find(consts::HORIZON_NAME) != std::string::npos)
                        return Object::TypeOfFixture::FIX_HORIZON;
                    else if (name.find(consts::WORLD_BUNDARIES_NAME) != std::string::npos)
                        return Object::TypeOfFixture::FIX_WORLD_BUDARIES;
                    else
                        return Object::TypeOfFixture::FIX_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Shape no implemented");
                    return Object::TypeOfFixture::FIX_NONE;
                }
            }
            
            static std::string getFixtureName(b2Fixture* fixture)
            {
                //Object* obj = (Object*) fixture->GetUserData();
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    std::string* name  = static_cast<std::string*>(fixture->GetUserData());
                    if (name != nullptr && name->find(consts::FOOT_NAME) != std::string::npos)
                        return *name;
                    else
                    {
                        sprite = static_cast<Sprite*>(fixture->GetUserData());
                        if (sprite != nullptr)
                            return  sprite->getName();
                        else
                            return std::string();
                    }
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getBodyName: Circle no implemented");
                    return "Nothing";
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    char* name = static_cast<char*>(body->GetUserData());
                    return std::string(name);
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getBodyName: Shape no implemented");
                    return "Nothing";
                }
            }
            
            
        };
    }
}


#endif
