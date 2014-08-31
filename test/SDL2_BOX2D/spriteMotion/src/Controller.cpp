#include "Controller.hpp"
#include "Constants.hpp"

namespace barrio {
    
    void Controller::Create(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera)
    {
        this->renderer = renderer;
        this->physicsWorld = physicsWorld;
        this->camera = camera;
    }    
    
    void Controller::loadLevelWord(const Level level)
    {
        camera->loadBackGroundImage("img/backgorund_1679x600.png", renderer);
        
        playerA.CreateCharacter("PlayerONE", Sprite::TypeOfSprite::CHARACTER, Sprite::TypeOfShape::POLYGON, renderer);
        playerA.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 15.0);
        playerA.setMovement(Sprite::direcction::UP, SDL_SCANCODE_UP);
        playerA.setMovement(Sprite::direcction::DOWN, SDL_SCANCODE_DOWN);
        playerA.setMovement(Sprite::direcction::LEFT, SDL_SCANCODE_LEFT);
        playerA.setMovement(Sprite::direcction::RIGHT, SDL_SCANCODE_RIGHT);
        playerA.setMovement(Sprite::direcction::PUNCH, SDL_SCANCODE_SPACE);
        physicsWorld->addToWorld("PlayerONE", &playerA, SDL_Point{600, 550}, playerA.getAnimationSize("stop"),
                                 consts::DYNAMIC_BODY, consts::DISABLE_ROTATION);
        
        physicsWorld->tmpGround();
                
        playerB.CreateCharacter("PlayerTWO", Sprite::TypeOfSprite::CHARACTER, Sprite::TypeOfShape::POLYGON, renderer);
        playerB.loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 5.0);
        playerB.setMovement(Sprite::direcction::UP, SDL_SCANCODE_W);
        playerB.setMovement(Sprite::direcction::DOWN, SDL_SCANCODE_S);
        playerB.setMovement(Sprite::direcction::LEFT, SDL_SCANCODE_A);
        playerB.setMovement(Sprite::direcction::RIGHT, SDL_SCANCODE_D);
        physicsWorld->addToWorld("PlayerTWO", &playerB, SDL_Point{700, 580}, playerB.getAnimationSize("stop"),
                                 consts::DYNAMIC_BODY, consts::DISABLE_ROTATION);
        
        furnitures.CreateFurnitures("ObjectsGroup", Sprite::TypeOfSprite::FURNITURE, Sprite::TypeOfShape::POLYGON, renderer, SDL_Color{0, 255, 0, 0});
        furnitures.loadFurnitures("conf/spriteSheets/furniture_1.json", "img/furnitures_1.png", 2.0, 2.0);
        physicsWorld->addToWorld("objeto1", &furnitures, SDL_Point{400, 400}, furnitures.getFurnitureSize("objeto1"),
                                 consts::STATIC_BODY, consts::DISABLE_ROTATION);
    }
    
    bool Controller::handleSystem(void)
    {
        if (handleGameState(&event) == consts::QUIT_GAME)
            return consts::QUIT_GAME;
        else
        {
            handleInputPlayer(playerA);
            handleInputPlayer(playerB);
            return consts::CONTINUE_GAME;
        }
    }
    
    void Controller::handleInputPlayer(Character& player)
    {
        float32 vel = 1.90f;
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if (currentKeyStates[player.movements[Sprite::direcction::UP]] )
        {
            physicsWorld->getBody(player.spriteName)->SetLinearVelocity({0.0f, -vel});
            player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::direcction::DOWN]] )
        {
            physicsWorld->getBody(player.spriteName)->SetLinearVelocity({0.0f, vel});
            player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::direcction::LEFT]] )
        {
            physicsWorld->getBody(player.spriteName)->SetLinearVelocity({-vel, 0.0f});
            player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::direcction::RIGHT]] )
        {
            physicsWorld->getBody(player.spriteName)->SetLinearVelocity({vel, 0.0f});
            player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else if (currentKeyStates[player.movements[Sprite::direcction::PUNCH]] )
        {
            physicsWorld->getBody(player.spriteName)->SetLinearVelocity({0.0f, 0.0f});
            player.playAnimation("punch", consts::DELAY_BETWEEN_ANIMATIONS);
        }
        else
        {
            player.playAnimation("stop", consts::DELAY_BETWEEN_ANIMATIONS);
            if (player.isAnimationStop())
            {
                physicsWorld->getBody(player.spriteName)->SetLinearVelocity({0.0f, 0.0f});                
            }
        }
    }

    
    bool Controller::handleGameState(SDL_Event* event)
    {
        bool quit = consts::CONTINUE_GAME;
        static Uint32 ms = 0;
        while( SDL_PollEvent( event ) != 0 )
        {
            if( event->type == SDL_QUIT )
            {
                quit = consts::QUIT_GAME;
            }
            else if ( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
            {
                quit = consts::QUIT_GAME;
            }
            else
            {
                if (event->type == SDL_WINDOWEVENT)
                {
                    switch (event->window.event)
                    {
                        case SDL_WINDOWEVENT_SHOWN:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d shown", event->window.windowID);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_HIDDEN:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d hidden", event->window.windowID);
                            ms = consts::RESUME_STATE_DELAY_IN_MS;
                            break;
                        case SDL_WINDOWEVENT_EXPOSED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d exposed", event->window.windowID);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_MOVED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d moved to %d,%d",
                                           event->window.windowID, event->window.data1,
                                           event->window.data2);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d resized to %dx%d",
                                           event->window.windowID, event->window.data1,
                                           event->window.data2);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_MINIMIZED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d minimized", event->window.windowID);
                            ms = consts::RESUME_STATE_DELAY_IN_MS;
                            break;
                        case SDL_WINDOWEVENT_MAXIMIZED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE,"Window %d maximized", event->window.windowID);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_RESTORED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d restored", event->window.windowID);
                            ms = 0;;
                            break;
                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d gained keyboard focus",
                                           event->window.windowID);
                            ms = 0;
                            break;
                        case SDL_WINDOWEVENT_FOCUS_LOST:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d lost keyboard focus",
                                           event->window.windowID);
                            ms = consts::RESUME_STATE_DELAY_IN_MS;
                            break;
                        case SDL_WINDOWEVENT_CLOSE:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d closed", event->window.windowID);
                            ms = consts::RESUME_STATE_DELAY_IN_MS;
                            break;
                        default:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Window %d got unknown event %d",
                                           event->window.windowID, event->window.event);
                            ms = 0;
                            break;
                    }
                }
            }
        }
        
        SDL_Delay(ms);
        return quit;
    }
    
}

