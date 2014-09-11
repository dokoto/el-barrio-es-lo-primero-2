#ifndef EL_BARRIO_ES_LO_PRIMERO_Fixtures_h
#define EL_BARRIO_ES_LO_PRIMERO_Fixtures_h

#include "Names.hpp"

namespace barrio
{
    namespace utls
    {
        class Fixture
        {
        public:
            
            static entity::TypeOfSprite getTypeOfSprite(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                        return  sprite->getBody()->getTypeOfSprite();
                    else
                        return entity::TypeOfSprite::SPRT_NONE;
                    
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Circle no implemented");
                    return entity::TypeOfSprite::SPRT_NONE;
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    return entity::TypeOfSprite::SPRT_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Shape no implemented");
                    return entity::TypeOfSprite::SPRT_NONE;
                }
            }
            
            static entity::TypeOfShape getTypeOfShape(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                        return  sprite->getBody()->getTypeOfShape();
                    else
                        return entity::TypeOfShape::SHP_POLYGON;
                    
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    return entity::TypeOfShape::SHP_CIRCLE;
                }
                else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    return entity::TypeOfShape::SHP_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfShape: Shape no implemented");
                    return entity::TypeOfShape::SHP_NONE;
                }
            }
            
            static void* getCharcaterUserData(b2Body* body)
            {
                Object* obj = nullptr;
                for (b2Fixture* fixtureElement = body->GetFixtureList(); fixtureElement; fixtureElement = fixtureElement->GetNext())
                {
                    obj = static_cast<Object*>(fixtureElement->GetUserData());
                    if (obj->whoAmI() == Glob::Classes::CLASS_OBJECT)
                        continue;
                    else if (obj->whoAmI() == Glob::Classes::CLASS_TEXTURE)
                        return fixtureElement->GetUserData();
                    else
                        continue;
                }
                return nullptr;
            }
            
            static entity::TypeOfFixture getTypeOfFixture(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    sprite = static_cast<Sprite*>(fixture->GetUserData());
                    if (sprite != nullptr)
                    {
                        std::string name = getFixtureName(fixture);
                        if(name.find(name::FOOT_NAME) != std::string::npos)
                            return entity::TypeOfFixture::FIX_FOOT;
                        else if (sprite->getBody()->getTypeOfSprite() == entity::TypeOfSprite::SPRT_CHARACTER)
                            return entity::TypeOfFixture::FIX_CHARACTER;
                        else if (sprite->getBody()->getTypeOfSprite() == entity::TypeOfSprite::SPRT_FURNITURE)
                            return entity::TypeOfFixture::FIX_FURNITURE;
                        else
                            return entity::TypeOfFixture::FIX_NONE;
                        
                    }
                    else
                        return entity::TypeOfFixture::FIX_NONE;
                    
                }
                else if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Circle no implemented");
                    return entity::TypeOfFixture::FIX_NONE;
                }
                else if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
                {
                    std::string name = getFixtureName(fixture);
                    if (name.find(name::HORIZON_NAME) != std::string::npos)
                        return entity::TypeOfFixture::FIX_HORIZON;
                    else if (name.find(name::WORLD_BUNDARIES_NAME) != std::string::npos)
                        return entity::TypeOfFixture::FIX_WORLD_BUDARIES;
                    else
                        return entity::TypeOfFixture::FIX_NONE;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Shape no implemented");
                    return entity::TypeOfFixture::FIX_NONE;
                }
            }
            
            static std::string getFixtureName(b2Fixture* fixture)
            {
                b2Body* body = fixture->GetBody();
                Object* obj = nullptr;
                if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
                {
                    Sprite* sprite = nullptr;
                    obj = static_cast<Object*>(fixture->GetUserData());
                    if (obj != nullptr && obj->getName().find(name::FOOT_NAME) != std::string::npos)
                        return obj->getName();
                    else
                    {
                        sprite = static_cast<Sprite*>(fixture->GetUserData());
                        if (sprite != nullptr)
                        {
                            Object* obj = static_cast<Object*>(body->GetUserData());
                            if (obj->getTypeOfFixture() == entity::TypeOfFixture::FIX_FURNITURE)
                            {
                                return obj->getName();
                            }
                            else
                            {
                                return  sprite->getBody()->getName();
                            }
                        }
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
