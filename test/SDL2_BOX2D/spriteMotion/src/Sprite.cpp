#include "Sprite.hpp"
#include "errorsCodes.hpp"

namespace barrio {
    
    using namespace std;
    
    void Sprite::CreateSprite(const std::string& spriteName, TypeOfSprite typeOfSprite, TypeOfShape typeOfShape, SDL_Color transparentColor, bool followWithCamera)
    {
        this->spriteName = spriteName;
        if (typeOfShape == TypeOfShape::POLYGON && ( typeOfSprite == TypeOfSprite::CHARACTER || typeOfSprite == TypeOfSprite::ENEMY ) )
            this->spriteFootName = spriteName + consts::FOOT_NAME;
        this->followWithCamera = followWithCamera;
        this->typeOfSprite = typeOfSprite;
        this->typeOfShape = typeOfShape;
        setTransparentColor(transparentColor);
    }
    
    Sprite::typeOfFixture Sprite::getFixtureTypeOfFixture(b2Fixture *fixture)
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
                    return Sprite::typeOfFixture::FIX_FOOT;
                else if (sprite->getTypeOfSprite() == Sprite::TypeOfSprite::CHARACTER)
                    return Sprite::typeOfFixture::FIX_CHARACTER;
                else if (sprite->getTypeOfSprite() == Sprite::TypeOfSprite::ENEMY)
                    return Sprite::typeOfFixture::FIX_ENEMY;
                else if (sprite->getTypeOfSprite() == Sprite::TypeOfSprite::FURNITURE)
                    return Sprite::typeOfFixture::FIX_FURNITURE;
                
            }
            else
                return Sprite::typeOfFixture::FIX_TYPE_OF_FIXTURE_NONE;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Circle no implemented");
            return Sprite::typeOfFixture::FIX_TYPE_OF_FIXTURE_NONE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            string name = getFixtureName(fixture);
            if (name.find("HORIZON") != string::npos)
                return Sprite::typeOfFixture::FIX_HORIZON;
            else if (name.find("WORLD_BUDARIES") != string::npos)
                return Sprite::typeOfFixture::FIX_WORLD_BUDARIES;
            else
                return Sprite::typeOfFixture::FIX_TYPE_OF_FIXTURE_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfFixture: Shape no implemented");
            return Sprite::typeOfFixture::FIX_TYPE_OF_FIXTURE_NONE;
        }
    }
    
    Sprite::TypeOfShape Sprite::getFixtureTypeOfShape(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            sprite = static_cast<Sprite*>(fixture->GetUserData());
            if (sprite != nullptr)
                return  sprite->getTypeOfShape();
            else
                return Sprite::TypeOfShape::POLYGON;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            return Sprite::TypeOfShape::CIRCLE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            return Sprite::TypeOfShape::TYPE_OF_SHAPE_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfShape: Shape no implemented");
            return Sprite::TypeOfShape::TYPE_OF_SHAPE_NONE;
        }
    }
    
    Sprite::TypeOfSprite Sprite::getFixtureTypeOfSprite(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetFixtureList()->GetType() == b2Shape::e_polygon)
        {
            Sprite* sprite = nullptr;
            sprite = static_cast<Sprite*>(fixture->GetUserData());
            if (sprite != nullptr)
                return  sprite->getTypeOfSprite();
            else
                return Sprite::TypeOfSprite::TYPE_OF_SPRITE_NONE;
            
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_circle)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Circle no implemented");
            return Sprite::TypeOfSprite::TYPE_OF_SPRITE_NONE;
        }
        else  if (body->GetFixtureList()->GetType() == b2Shape::e_chain)
        {
            return Sprite::TypeOfSprite::TYPE_OF_SPRITE_NONE;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "getFixtureTypeOfSprite: Shape no implemented");
            return Sprite::TypeOfSprite::TYPE_OF_SPRITE_NONE;
        }
    }
    
    std::string Sprite::getFixtureName(b2Fixture* fixture)
    {
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
                    return  sprite->spriteName;
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


