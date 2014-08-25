#include "Render.hpp"
#include "errorsCodes.hpp"
#include "Colors.hpp"
#include "Character.hpp"
#include "Furnitures.hpp"

namespace barrio {
    
    void Render::CreateRender(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera)
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
    }
    
    void Render::clearScreen(void)
    {
        SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
        SDL_RenderClear( renderer );
    }
    
    void Render::drawBackGround(void)
    {
        auto itPlayer = physicsWorld->bodiesBySpriteType.find(Sprite::TypeOfSprite::CHARACTER);
        if (itPlayer != physicsWorld->bodiesBySpriteType.end())
        {
            camera->cameraFollowObj(Utils::fullConversionCartesianPosToScreenPos(itPlayer->second), camera->cameraPosition);
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
        SDL_Point tmpSpritePosition = {0 ,0};
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        
        auto itCharacters = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::CHARACTER);
        for (auto itElems = itCharacters.first; itElems != itCharacters.second; itElems++)
        {
            tmpCharacter = static_cast<Character*>(itElems->second->GetUserData());
            tmpSpritePosition = Utils::fullConversionCartesianPosToScreenPos(itElems->second);
            origin = tmpCharacter->getCurrentClip();
            destination = {tmpSpritePosition.x, tmpSpritePosition.y, origin.w, origin.h};
            SDL_RenderCopy(renderer, tmpCharacter->getSDLTexture(), &origin, &destination);
        }
    }
    
    void Render::drawEnemies()
    {
        Character* tmpCharacter = nullptr;
        SDL_Point tmpSpritePosition = {0 ,0};
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        
        auto itCharacters = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::ENEMY);
        for (auto itElems = itCharacters.first; itElems != itCharacters.second; itElems++)
        {
            tmpCharacter = static_cast<Character*>(itElems->second->GetUserData());
            tmpSpritePosition = Utils::fullConversionCartesianPosToScreenPos(itElems->second);
            origin = tmpCharacter->getCurrentClip();
            destination = {tmpSpritePosition.x, tmpSpritePosition.y, origin.w, origin.h};
            SDL_RenderCopy(renderer, tmpCharacter->getSDLTexture(), &origin, &destination);
        }
    }
    
    void Render::drawFurnitures()
    {
        Furnitures* tmpFurniture= nullptr;
        SDL_Rect origin = {0, 0, 0, 0};
        SDL_Rect destination = {0, 0, 0, 0};
        SDL_Point furniturePosDest = {0, 0};
        
        // Nos traemos todos los objetos fisicos que sean de tipo FURNIURE
        auto itFurnituresGroup = physicsWorld->bodiesBySpriteType.equal_range(Sprite::TypeOfSprite::FURNITURE);
        // Iteramos todos los FURNITURES
        for (auto itGroup = itFurnituresGroup.first; itGroup != itFurnituresGroup.second; itGroup++)
        {
            // Obtenemos el tipo Furniture* del user data del engine fisico
            tmpFurniture = static_cast<Furnitures*>(itGroup->second->GetUserData());
            // Obtenemos todos los Clip de furnitures que existen dentro de la texture
            auto itFurnituresElems = tmpFurniture->getAllFurnitures();
            for (auto itElem = itFurnituresElems.begin(); itElem != itFurnituresElems.end(); itElem++)
            {
                origin = itElem->second;
                auto itFurniturePosition = physicsWorld->bodiesByName.find(itElem->first);
                if (itFurniturePosition != physicsWorld->bodiesByName.end())
                {
                    furniturePosDest = Utils::fullConversionCartesianPosToScreenPos(itFurniturePosition->second);
                    destination = {furniturePosDest.x, furniturePosDest.y, origin.w, origin.h};
                    SDL_RenderCopy(renderer, tmpFurniture->getSDLTexture(), &origin, &destination);
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Furniture no found %d", itElem->first.c_str());
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
    
    void Render::drawDebug(void)
    {
        clearScreen();
        drawBackGround();
        drawPhysicWorld();
        step();
    }
    
    void Render::step()
    {
        physicsWorld->Step();
        SDL_RenderPresent(renderer);
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
            
            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
            
            if (shapeType == b2Shape::e_polygon)
            {
                b2Vec2 points[4];
                for(int i=0;i<4;i++)
                {
                    points[i]=((b2PolygonShape*)ptr->GetFixtureList()->GetShape())->GetVertex(i);
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
            else if (shapeType == b2Shape::e_chain)
            {
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





