#include <cmath>
#include "Colors.hpp"
#include "Camera.hpp"
#include "errorsCodes.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Furnitures.hpp"

namespace barrio {
    using namespace std;
    
    void Camera::CreateCamera(const float32 camera_width, const float32 camera_heigth,
                              const float32 world_width, const float32 world_height)
    {
        this->camera_position.x = 0;
        this->camera_position.y = 0;
        this->camera_width = camera_width;
        this->camera_height = camera_heigth;
        this->world_width = world_width;
        this->world_height = world_height;
        this->world_middle_height = this->world_height / 2;
        this->world_middle_width = this->world_width / 2;
        this->camera_middle_height = this->camera_height / 2;
        this->camera_middle_width = this->camera_width / 2;
        this->shift_factor = 0.05f;
        this->oldCartesianPosOfFollowSprite.x = 0.0f;
        this->oldCartesianPosOfFollowSprite.y = 0.0f;
    }
    
    Camera::~Camera(void)
    {
        spriteToFollow = nullptr;
        printf("Destroing Camera\n");
    }
    
    void Camera::renderBackGround(SDL_Renderer*& renderer)
    {
        if (this->background.isEmpty())
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Camera background not found");
            throw error::CAMERA_NO_BACKGROUND_FOUND;
        }
        else
        {
            if (this->spriteToFollow != nullptr)
            {
                SDL_Point ScreenPoint = spriteToFollow->getScreenPosition(spriteToFollow->getSpriteName());
                this->cameraFollowObj(ScreenPoint, this->camera_position);
            }
            else
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Camera has not an item to follow");
            }
            
            SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
            SDL_RenderClear( renderer );
            SDL_Rect clipOrigin {camera_position.x, camera_position.y, static_cast<int>(camera_width), static_cast<int>(camera_height)};
            SDL_Rect clipDestination = {0, 0, static_cast<int>(camera_width), static_cast<int>(camera_height)};
            
            this->render(Clip {"background", clipOrigin, clipDestination}, renderer, &background);
        }
    }
    
    void Camera::renderClip(const Clip& clip, SDL_Renderer*& renderer, Texture* obj)
    {
        this->renderObj(clip, renderer, obj);
    }
    
    void Camera::renderDebugInfo(SDL_Renderer*& renderer, DebugInfo* obj)
    {
        const int pixelMargin = 20;
        SDL_SetRenderDrawColor(renderer, color::BLACK, color::BLACK, color::BLACK, color::WHITE);
        SDL_Rect r = SDL_Rect{2, 2, obj->getPixelWidth()+pixelMargin, obj->getPixelHeight()+pixelMargin};
        SDL_RenderFillRect(renderer, &r);
        
        SDL_SetRenderDrawColor(renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE);
        SDL_RenderDrawLine(renderer, consts::CAMERA_WIDTH_PX/2, 0, consts::CAMERA_WIDTH_PX/2, consts::CAMERA_HEIGHT_PX);
        SDL_RenderDrawLine(renderer, 0, consts::CAMERA_HEIGHT_PX/2, consts::CAMERA_WIDTH_PX, consts::CAMERA_HEIGHT_PX/2);
        
        SDL_Rect renderQuad = { 10, 10, obj->getPixelWidth(), obj->getPixelHeight() };
        SDL_RenderCopy( renderer, obj->getTexture(), NULL, &renderQuad );
    }
    
    void Camera::renderObj(const Clip& clip, SDL_Renderer*& renderer, Texture* obj)
    {
        this->render(clip, renderer, obj, clip.destinationAngle, SDL_Point{0, 0}, (obj->getToFlip())? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE );
    }
    
    void Camera::render(const Clip& clip, SDL_Renderer*& renderer, Texture* obj, double angle, SDL_Point center, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx( renderer, obj->getSDLTexture(), &clip.screenOrigin, &clip.screenDestination, angle, &center, flip );
    }
    
    void Camera::DrawPhysicsWorld(b2World* physicsWorld, SDL_Renderer*& renderer)
    {
        b2Body* tmp= physicsWorld->GetBodyList();
        b2Vec2 points[4];
        b2Fixture* fixture = nullptr;
        b2Shape::Type shapeType;
        b2Vec2 point;
        while(tmp)
        {
            fixture = tmp->GetFixtureList();
            shapeType = fixture->GetType();
            
            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
            
            if (shapeType == b2Shape::e_polygon)
            {
                for(int i=0;i<4;i++)
                {
                    points[i]=((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
                    Utils::rotateTranslate(points[i],tmp->GetWorldCenter(),tmp->GetAngle());
                }
                
                SDL_Point pointA = Utils::convCartesianPosToScreennPos(points[0]);
                SDL_Point pointB = Utils::convCartesianPosToScreennPos(points[1]);
                SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                
                pointA = Utils::convCartesianPosToScreennPos(points[1]);
                pointB = Utils::convCartesianPosToScreennPos(points[2]);
                SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                
                pointA = Utils::convCartesianPosToScreennPos(points[2]);
                pointB = Utils::convCartesianPosToScreennPos(points[3]);
                SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
                
                pointA = Utils::convCartesianPosToScreennPos(points[3]);
                pointB = Utils::convCartesianPosToScreennPos(points[0]);
                SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
            }
            else if (shapeType == b2Shape::e_chain)
            {
                b2ChainShape* chain = (b2ChainShape*)tmp->GetFixtureList()->GetShape();
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
            
            tmp=tmp->GetNext();
        }
    }
    
    void Camera::cameraFollowObj(const SDL_Point& screenPosition, SDL_Point& camera_position)
    {
        if (camera_position.x + camera_width > screenPosition.x &&  camera_position.x <= screenPosition.x)
        {
            if ( (screenPosition.x - camera_position.x) < consts::CAMERA_MARGIN_PX)
            {
                if (camera_position.x > 0)
                {
                    if (camera_position.x - consts::CAMERA_MARGIN_PX > 0)
                    {
                        shift_factor = consts::CAMERA_MARGIN_PX - (screenPosition.x - camera_position.x);
                        camera_position.x -= shift_factor;
                    }
                    else
                    {
                        camera_position.x -= 1;
                    }
                }
            }
            else if ((screenPosition.x - camera_position.x) > (camera_width - consts::CAMERA_MARGIN_PX))
            {
                if ((world_width-camera_position.x) > camera_width)
                {
                    if (camera_position.x + camera_width < world_width - consts::CAMERA_MARGIN_PX)
                    {
                        shift_factor = std::abs((camera_width - consts::CAMERA_MARGIN_PX) - (screenPosition.x - camera_position.x));
                        camera_position.x += shift_factor;
                    }
                    else
                    {
                        camera_position.x += 1;
                    }
                }
            }
        }
        else
        {
            if (screenPosition.x < camera_middle_width)
            {
                camera_position.x = 0;
            }
            else if (world_width - screenPosition.x < camera_middle_width)
            {
                camera_position.x = static_cast<int>(world_width - camera_width);
            }
            else
            {
                camera_position.x = static_cast<int>(screenPosition.x - camera_middle_width);
            }
        }
    }
}