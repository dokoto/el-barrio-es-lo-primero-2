#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, Object::TypeOfSprite typeOfSprite, Object::TypeOfShape typeOfShape, Object::TypeOfFixture typeOfFixture,
                              SDL_Color transparentColor, bool followWithCamera)
    {
        if (typeOfShape == TypeOfShape::SHP_POLYGON && ( typeOfSprite == TypeOfSprite::SPRT_CHARACTER || typeOfSprite == TypeOfSprite::SPRT_ENEMY ) )
        {
            foot.CreateObject(spriteName + consts::FOOT_NAME, TypeOfSprite::SPRT_NONE, TypeOfShape::SHP_POLYGON, TypeOfFixture::FIX_FOOT);
        }
                
        CreateObject(spriteName, typeOfSprite, typeOfShape, typeOfFixture);
        this->setTransparentColor(transparentColor);
        this->followWithCamera = followWithCamera;
    }
    
    Object::TypeOfFixture Sprite::getFixtureTypeOfFixture(b2Fixture *fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            sprite = static_cast<Sprite*>(fixture->GetUserData());
            if (sprite != nullptr)
            {
                string name = getFixtureName(fixture);
                if(name.find(consts::FOOT_NAME) != string::npos)
                    return TypeOfFixture::FIX_FOOT;
                else if (sprite->getTypeOfSprite() == TypeOfSprite::SPRT_CHARACTER)
                    return TypeOfFixture::FIX_CHARACTER;
                else if (sprite->getTypeOfSprite() == TypeOfSprite::SPRT_ENEMY)
                    return TypeOfFixture::FIX_ENEMY;
                else if (sprite->getTypeOfSprite() == TypeOfSprite::SPRT_FURNITURE)
                    return TypeOfFixture::FIX_FURNITURE;
                
            }
            else
                return TypeOfFixture::FIX_NONE;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Circle no implemented");
            return TypeOfFixture::FIX_NONE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            string name = getFixtureName(fixture);
            if (name.find(consts::HORIZON_NAME) != string::npos)
                return TypeOfFixture::FIX_HORIZON;
            else if (name.find(consts::WORLD_BUNDARIES_NAME) != string::npos)
                return TypeOfFixture::FIX_WORLD_BUDARIES;
            else
                return TypeOfFixture::FIX_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Shape no implemented");
            return TypeOfFixture::FIX_NONE;
        }
    }
    
    Object::TypeOfShape Sprite::getFixtureTypeOfShape(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            sprite = static_cast<Sprite*>(fixture->GetUserData());
            if (sprite != nullptr)
                return  sprite->getTypeOfShape();
            else
                return TypeOfShape::SHP_POLYGON;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            return TypeOfShape::SHP_CIRCLE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            return TypeOfShape::SHP_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfShape: Shape no implemented");
            return TypeOfShape::SHP_NONE;
        }
    }
    
    Object::TypeOfSprite Sprite::getFixtureTypeOfSprite(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            sprite = static_cast<Sprite*>(fixture->GetUserData());
            if (sprite != nullptr)
                return  sprite->getTypeOfSprite();
            else
                return TypeOfSprite::SPRT_NONE;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Circle no implemented");
            return TypeOfSprite::SPRT_NONE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            return Sprite::TypeOfSprite::SPRT_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Shape no implemented");
            return TypeOfSprite::SPRT_NONE;
        }
    }
    
    std::string Sprite::getFixtureName(b2Fixture* fixture)
    {
        Object* obj = (Object*) fixture->GetUserData();
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            string* name  = static_cast<string*>(fixture->GetUserData());
            if (name != nullptr && name->find(consts::FOOT_NAME) != string::npos)
                return *name;
            else
            {
                sprite = static_cast<Sprite*>(fixture->GetUserData());
                if (sprite != nullptr)
                    return  sprite->getName();
                else
                    return string();
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
            return string(name);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getBodyName: Shape no implemented");
            return "Nothing";
        }
        
    }
    
}


