#include "Game.hpp"


#include <stdexcept>
#include <sstream>
#include "errorsCodes.hpp"
#include "Colors.hpp"
#include "Constants.hpp"
#include "Clip.hpp"


namespace barrio {
    
    using namespace std;
    
    Game::Game() :    
        window{nullptr},
        renderer{nullptr}
    
    {
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "SDL2 system initialization has failed because: %s", SDL_GetError());
            throw error::SYS_INIT_FAIL;
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "SDL2 system is initilization...OK");
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Linear texture filtering initialization has failed because: %s", SDL_GetError());
                throw error::LINEAR_TEXTURE_FAIL;
            }
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Linear texture filtering initilization...OK");
            
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, consts::CAMERA_WIDTH_PX, consts::CAMERA_HEIGHT_PX, SDL_WINDOW_SHOWN );
            if( window == NULL )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Window initialization has failed because: %s", SDL_GetError());
                throw error::WINDOW_INIT_FAIL;
            }
            else
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window initialization...OK");
                renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
                if( renderer == NULL )
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Render creation has failed because: %s", SDL_GetError());
                    throw error::RENDER_CREATION_FAIL;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Render creation...OK");
                    SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
                    int imgFlags = IMG_INIT_PNG;
                    if( !( IMG_Init( imgFlags ) & imgFlags ) )
                    {
                        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "SDL2 image system initialization has failed because: %s", SDL_GetError());
                        throw error::SYS_IMAGE_INIT_FAIL;
                    }
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "SDL2 image system initialization...OK");
                    physicsWorld.CreateWorld(b2Vec2{0.0f, 0.0f}, consts::WORLD_WIDTH_PX / consts::PHYSICS_CONV_FACTOR_PX, consts::WORLD_HEIGHT_PX / consts::PHYSICS_CONV_FACTOR_PX);
                    camera.CreateCamera(consts::CAMERA_WIDTH_PX, consts::CAMERA_HEIGHT_PX, consts::WORLD_WIDTH_PX, consts::WORLD_HEIGHT_PX);
                }
            }
            
            if (TTF_Init() < 0)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "SDL2 TTF system initialization has failed because: %s", SDL_GetError());
                throw error::SYS_INIT_TTF_FAIL;
            }
            else
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "TTF system initialization...OK");
        }
    }
    
    Game::~Game()
    {
        //Destroy window
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Destroy Render...OK");
        SDL_DestroyRenderer( renderer );
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Destroy Window...OK");
        SDL_DestroyWindow( window );
        window = NULL;
        renderer = NULL;
        
        //Quit SDL subsystems
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Shutdown SDL2 System...OK");
        IMG_Quit();
        SDL_Quit();
    }
    
    void Game::loadMedia(void)
    {
        debugInfo.CreateDebugInfo("ttf/ArialNarrowRegular.ttf", 15);
        camera.setBackground("img/backgorund_1679x600.png", renderer);
        
        players[0].CreateCharacter("player1", renderer, &physicsWorld);
        players[1].CreateCharacter("player2", renderer, &physicsWorld);

        //player.loadAnimations("conf/spriteSheets/foo.json", "img/foo.png");
        //players[0].loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 8.0, 8.0);
        
        //players[0].loadAnimations("conf/spriteSheets/player1.json", "img/player1.png", 2.0, 2.0);
        //players[1].loadAnimations("conf/spriteSheets/player2.json", "img/player2.png", 2.0, 2.0);
        
        players[0].loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 5.0, 15.0);
        //players[1].loadAnimations("conf/spriteSheets/point10x5px.json", "img/point10x5px.png", 16.0, 16.0);
        
        players[0].addToPhysicsWorld(-5.0f, -3.0f);
        //players[1].addToPhysicsWorld(-5.3f, -4.0f);
        
        furnitures.CreateFurnitures("furnituresTest", renderer, &physicsWorld, SDL_Color{0, 255, 0, 0});
        furnitures.loadFurnitures("conf/spriteSheets/furniture_1.json", "img/furnitures_1.png");
        furnitures.addToPhysicsWorld("objeto1", -6.0f, 2.0f);
        //furnitures.addToPhysicsWorld("objeto2", 6.0f, 2.0f);
        
        camera.follow(&players[0]);
    }
    
    string Game::createDebugText()
    {
        std::stringstream os;
        os << "[ " << roundf(players[0].getPosition().x * 100.00f) / 100.00f << " , " << roundf(players[0].getPosition().y * 100.00f) / 100.00f << " ]";
        return os.str();
    }
    
    bool Game::handlePoolEvents(SDL_Event* event)
    {
        bool quit = false;
        static Uint32 ms = 0;
        while( SDL_PollEvent( event ) != 0 )
        {
            if( event->type == SDL_QUIT )
            {
                quit = true;
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
                            ms = 300;
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
                            ms = 300;
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
                            ms = 300;
                            break;
                        case SDL_WINDOWEVENT_CLOSE:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d closed", event->window.windowID);
                            ms = 300;
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
    
    void Game::gameLoop(void)
    {
        bool quit = false;
        SDL_Event e;
        string acction;
        b2Vec2 velocity;
        
        loadMedia();
        while (quit == false)
        {
            quit = handlePoolEvents(&e);
            physicsWorld.Step();
            camera.renderBackGround(renderer);
            
            debugInfo.writeText(createDebugText(), SDL_Color{246, 0, 4, 0}, renderer);
            camera.renderDebugInfo(renderer, &debugInfo);
            
            camera.renderClip(furnitures.getFurnitureClip("objeto1"), renderer, &furnitures);
            //camera.renderClip(furnitures.getFurnitureClip("objeto2"), renderer, &furnitures);
            
            handleKeyBoard1(acction, velocity);
            players[0].setVelocity(velocity);
            camera.renderClip(players[0].playAnimation(acction, consts::DELAY_BETWEEN_ANIMATIONS), renderer, &players[0]);
            
            //handleKeyBoard2(acction, velocity);
            //players[1].setVelocity(velocity);
            //camera.renderClip(players[1].playAnimation(acction, consts::DELAY_BETWEEN_ANIMATIONS), renderer, &players[1]);
            
            //camera.switchFlipOFF();
            
            
            
            
            SDL_RenderPresent( renderer );
        }
    }
    
    void Game::handleKeyBoard1(std::string& action, b2Vec2& velocity)
    {
        float32 vel = 1.90f;
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
            velocity = {0.0f, vel};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
        {
            velocity = {0.0f, -vel};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            players[0].setToFlip(true);
            velocity = {-vel, 0.0f};
            action = "walking";
          }
        else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
            players[0].setToFlip(false);
            velocity = {vel, 0.0f};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
        {
            velocity = {0.0f, 0.0f};
            action = "punch";
        }
        else
        {
            if (players[0].isAnimationStop())
            {
                velocity = {0.0f, 0.0f};
                action = "stop";
            }
        }

    }
    
    void Game::handleKeyBoard2(std::string& action, b2Vec2& velocity)
    {
        float32 vel = 1.90f;
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if( currentKeyStates[ SDL_SCANCODE_W ] )
        {
            velocity = {0.0f, vel};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_S ] )
        {
            velocity = {0.0f, -vel};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_A ] )
        {
            velocity = {-vel, 0.0f};
            action = "walking";
        }
        else if( currentKeyStates[ SDL_SCANCODE_D ] )
        {
            velocity = {vel, 0.0f};
            action = "walking";
        }
        else
        {
            velocity = {0.0f, 0.0f};
            action = "stop";
        }
        
    }
    
}
