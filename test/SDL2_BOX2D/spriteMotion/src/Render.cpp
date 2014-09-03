#include "Render.hpp"
#include "errorsCodes.hpp"
#include "Colors.hpp"
#include "Character.hpp"
#include "Furnitures.hpp"

namespace barrio {
    
    void Render::CreateRender(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts)
    {
        if (renderer == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Render pointer is null");
            throw error::RENDER_NULL;
        }
        
        if (physicsWorld == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Physics World pointer is null");
            throw error::RENDER_NULL;
        }
        
        this->renderer = renderer;
        this->physicsWorld = physicsWorld;
        this->camera = camera;
        this->texts = texts;
    }
    
    void Render::clearScreen(void)
    {
        SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
        SDL_RenderClear( renderer );
    }
    
    void Render::drawBackGround(void)
    {
        auto itPlayer = physicsWorld->bodiesBySpriteType.find(Sprite::TypeOfSprite::SPRT_CHARACTER);
        if (itPlayer != physicsWorld->bodiesBySpriteType.end())
        {
            camera->cameraFollowObj(Utils::fullConversionCartesianPosToScreenPos(itPlayer->second->GetFixtureList(),
                                                                                 itPlayer->second->GetWorldCenter(), itPlayer->second->GetAngle()), camera->cameraPosition);
            SDL_Rect origin = {camera->cameraPosition.x, camera->cameraPosition.y, consts::CAMERA_WIDTH_PX, consts::CAMERA_HEIGHT_PX};
            SDL_Rect destination = {0, 0, consts::CAMERA_WIDTH_PX, consts::CAMERA_HEIGHT_PX};
            SDL_RenderCopy(renderer, camera->backGround.getSDLTexture(), &origin, &destination);
        }
        else
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Main Players not found");
        
    }
    
    void Render::drawCharacters(void)
    {
        Character* tmpCharacter = nullptr;
        Object* obj = nullptr;
        SDL_Point tmpSpritePosition = {0 ,0};
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        
        auto itCharacters = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::SPRT_CHARACTER);
        for (auto itElems = itCharacters.first; itElems != itCharacters.second; itElems++)
        {            
            for (b2Fixture* fixtureElement = itElems->second->GetFixtureList(); fixtureElement; fixtureElement = fixtureElement->GetNext())
            {
                obj = static_cast<Object*>(fixtureElement->GetUserData());
                if (obj->whoAmI() == consts::CLASSES::OBJECT)
                {
                    if (obj->getTypeOfFixture() == Object::TypeOfFixture::FIX_FOOT)
                        continue;
                }
                else if (obj->whoAmI() == consts::CLASSES::TEXTURE)
                {
                    tmpCharacter = static_cast<Character*>(fixtureElement->GetUserData());
                    tmpSpritePosition = Utils::fullConversionCartesianPosToScreenPos(fixtureElement, itElems->second->GetWorldCenter(), itElems->second->GetAngle());
                    origin = tmpCharacter->getCurrentClip();
                    destination = {tmpSpritePosition.x-camera->cameraPosition.x, tmpSpritePosition.y, origin.w, origin.h};
                    SDL_RenderCopy(renderer, tmpCharacter->getSDLTexture(), &origin, &destination);
                }
            }
        }
    }
    
    void Render::drawEnemies()
    {
        Character* tmpCharacter = nullptr;
        Object* obj = nullptr;
        SDL_Point tmpSpritePosition = {0 ,0};
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        
        auto itCharacters = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::SPRT_ENEMY);
        for (auto itElems = itCharacters.first; itElems != itCharacters.second; itElems++)
        {
            for (b2Fixture* fixtureElement = itElems->second->GetFixtureList(); fixtureElement; fixtureElement = fixtureElement->GetNext())
            {
                obj = static_cast<Object*>(fixtureElement->GetUserData());
                if (obj->whoAmI() == consts::CLASSES::OBJECT)
                {
                    if (obj->getTypeOfFixture() == Object::TypeOfFixture::FIX_FOOT)
                        continue;
                }
                else if (obj->whoAmI() == consts::CLASSES::TEXTURE)
                {
                    tmpCharacter = static_cast<Character*>(fixtureElement->GetUserData());
                    tmpSpritePosition = Utils::fullConversionCartesianPosToScreenPos(fixtureElement, itElems->second->GetWorldCenter(), itElems->second->GetAngle());
                    origin = tmpCharacter->getCurrentClip();
                    destination = {tmpSpritePosition.x-camera->cameraPosition.x, tmpSpritePosition.y, origin.w, origin.h};
                    SDL_RenderCopy(renderer, tmpCharacter->getSDLTexture(), &origin, &destination);
                }
            }
        }
        
    }
    
    void Render::drawFurnitures()
    {
        Furnitures* tmpFurniture= nullptr;
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        SDL_Point furniturePosDest = {0, 0};
        b2Fixture* tmpFixture = nullptr;
        
        // Nos traemos todos los objetos fisicos que sean de tipo FURNIURE
        auto itFurnituresGroup = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::SPRT_FURNITURE);
        // Iteramos todos los FURNITURES
        for (auto itGroup = itFurnituresGroup.first; itGroup != itFurnituresGroup.second; itGroup++)
        {
            // Obtenemos el tipo Furniture* del user data del engine fisico
            tmpFixture = itGroup->second->GetFixtureList();
            if (tmpFixture->GetUserData() == nullptr)
                tmpFixture = tmpFixture->GetNext();
            tmpFurniture = static_cast<Furnitures*>(tmpFixture->GetUserData());
            // Obtenemos todos los Clip de furnitures que existen dentro de la texture
            auto itFurnituresElems = tmpFurniture->getAllFurnitures();
            for (auto itElem = itFurnituresElems.begin(); itElem != itFurnituresElems.end(); itElem++)
            {
                origin = itElem->second;
                auto itFurniturePosition = physicsWorld->bodiesByName.find(itElem->first);
                if (itFurniturePosition != physicsWorld->bodiesByName.end())
                {
                    furniturePosDest = Utils::fullConversionCartesianPosToScreenPos(tmpFixture, itFurniturePosition->second->GetWorldCenter(),
                                                                                    itFurniturePosition->second->GetAngle());
                    destination = {furniturePosDest.x-camera->cameraPosition.x, furniturePosDest.y, origin.w, origin.h};
                    SDL_RenderCopy(renderer, tmpFurniture->getSDLTexture(), &origin, &destination);
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Furniture no found %s", itElem->first.c_str());
                }
            }
        }
    }
    
    void Render::draw(void)
    {
        clearScreen();
        drawBackGround();
        drawCharacters();
        drawEnemies();
        drawFurnitures();
        step();
    }
    
    void Render::drawDebugPrimitives(float avgFPS)
    {
        clearScreen();
        drawBackGround();
        drawPhysicWorld();
        drawDebugText(avgFPS);
        step();
    }
    
    void Render::drawDebug(float avgFPS)
    {
        clearScreen();
        drawBackGround();
        drawCharacters();
        drawEnemies();
        drawFurnitures();
        drawPhysicWorld();
        drawDebugText(avgFPS);
        step();
    }     
    
    void Render::step()
    {
        physicsWorld->Step();
        SDL_RenderPresent(renderer);
    }
    
    void Render::drawDebugText(float avgFPS)
    {
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {10, 10, 0, 0};
        char line[10];
        
        memset(&line[0], 0, 10);
        sprintf(line, "%2.2f FPS", avgFPS);
        texts->renderText("ARIAL_12", line, SDL_Color{0, 0, 0, 0}, renderer);
        
        origin.w = destination.w = texts->getPixelWidth();
        origin.h = destination.h = texts->getPixelHeight();
        
        SDL_Rect fillRect = { 8, 8, texts->getPixelWidth()+2, texts->getPixelHeight()+2};
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0x00 );
        SDL_RenderFillRect( renderer, &fillRect );
        
        SDL_RenderCopy(renderer, texts->getTexture(), &origin, &destination);
    }
    
    void Render::drawPhysicWorld(void)
    {
        b2Body* ptr = physicsWorld->getWorld()->GetBodyList();
        b2Fixture* fixture = nullptr;
        b2Shape::Type shapeType;
        
        while(ptr)
        {
            fixture = ptr->GetFixtureList();
            shapeType = fixture->GetType();
            
            if (shapeType == b2Shape::e_polygon)
            {
                for (b2Fixture* fixtureElement = ptr->GetFixtureList(); fixtureElement; fixtureElement = fixtureElement->GetNext())
                {
                    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
                    b2Vec2 points[4];
                    for(int i=0;i<4;i++)
                    {
                        //points[i]=((b2PolygonShape*)ptr->GetFixtureList()->GetShape())->GetVertex(i);
                        points[i]=((b2PolygonShape*)fixtureElement->GetShape())->GetVertex(i);
                        Utils::rotateTranslate(points[i], ptr->GetWorldCenter(), ptr->GetAngle());
                    }
                    
                    SDL_Point pointA = Utils::convCartesianPosToScreennPos(points[0]);
                    SDL_Point pointB = Utils::convCartesianPosToScreennPos(points[1]);
                    pointA.x = pointA.x - camera->cameraPosition.x;
                    pointB.x = pointB.x - camera->cameraPosition.x;
                    SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                    
                    pointA = Utils::convCartesianPosToScreennPos(points[1]);
                    pointB = Utils::convCartesianPosToScreennPos(points[2]);
                    pointA.x = pointA.x - camera->cameraPosition.x;
                    pointB.x = pointB.x - camera->cameraPosition.x;
                    SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                    
                    pointA = Utils::convCartesianPosToScreennPos(points[2]);
                    pointB = Utils::convCartesianPosToScreennPos(points[3]);
                    pointA.x = pointA.x - camera->cameraPosition.x;
                    pointB.x = pointB.x - camera->cameraPosition.x;
                    SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                    
                    pointA = Utils::convCartesianPosToScreennPos(points[3]);
                    pointB = Utils::convCartesianPosToScreennPos(points[0]);
                    pointA.x = pointA.x - camera->cameraPosition.x;
                    pointB.x = pointB.x - camera->cameraPosition.x;
                    SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                }
            }
            else if (shapeType == b2Shape::e_chain)
            {
                SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );
                b2Vec2 point;
                b2ChainShape* chain = (b2ChainShape*)ptr->GetFixtureList()->GetShape();
                int numEdges = chain->GetChildCount();
                //int numVertices = chain->m_hasNextVertex ? numEdges : numEdges + 1;
                
                b2EdgeShape edgeShape;
                for (int i = 0; i < numEdges; i++)
                {
                    chain->GetChildEdge( &edgeShape, i );
                    SDL_Point pointA = Utils::convCartesianPosToScreennPos(edgeShape.m_vertex0);
                    SDL_Point pointB = Utils::convCartesianPosToScreennPos(edgeShape.m_vertex1);
                    pointA.x = pointA.x - camera->cameraPosition.x;
                    pointB.x = pointB.x - camera->cameraPosition.x;
                    SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                }
            }
            else if (shapeType == b2Shape::e_circle)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Draw Physics: Circle is not implemented, yet");
            }
            else
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Draw Physics: Shape no implemented");
            }
            
            ptr = ptr->GetNext();
        }
        
    }
    
}





