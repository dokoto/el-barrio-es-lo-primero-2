#include "Game.hpp"


#include <stdexcept>
#include <sstream>
#include "errorsCodes.hpp"
#include "Colors.hpp"
#include "Constants.hpp"
#include "Animation.hpp"


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
        player.CreateCharacter("player", renderer, &physicsWorld);
        //player.loadAnimations("conf/spriteSheets/player2.json", "img/player.png");
        //player.loadAnimations("conf/spriteSheets/player.json", "img/foo.png");
        player.loadAnimations("conf/spriteSheets/player3.json", "img/point10x5px.png");
        player.addToPhysicsWorld(0.0f, 0.0f);
        camera.follow(&player);
    }
    
    string Game::createDebugText()
    {
        std::stringstream os;
        os << "[" << player.getPosition().x << "," << player.getPosition().y << "]";
        return os.str();
    }
    
    void Game::gameLoop(void)
    {
        bool quit = false;
        SDL_Event e;
        loadMedia();
        float32 vel = 1.90f;
        
        while (quit == false)
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }
            
            physicsWorld.Step();
            camera.renderBackGround(renderer);
            
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] )
            {
                player.setVelocity(b2Vec2{0.0f, vel});
                camera.renderAnimation(player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS), renderer, &player);
            }
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
            {
                player.setVelocity(b2Vec2{0.0f, -vel});
                camera.renderAnimation(player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS), renderer, &player);
            }
            else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
                player.setVelocity(b2Vec2{-vel, 0.0f});
                camera.renderAnimation(player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS), renderer, &player);
            }
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            {
                player.setVelocity(b2Vec2{vel, 0.0f});
                camera.renderAnimation(player.playAnimation("walking", consts::DELAY_BETWEEN_ANIMATIONS), renderer, &player);
            }
            else
            {
                player.setVelocity(b2Vec2{0.0f, 0.0f});
                camera.renderAnimation(player.playAnimation("stop", consts::DELAY_BETWEEN_ANIMATIONS), renderer, &player);
            }
            
            debugInfo.writeText(createDebugText(), SDL_Color{255, 255, 255, 0}, renderer);
            camera.renderDebugInfo(renderer, &debugInfo);
            
            
            SDL_RenderPresent( renderer );
        }
    }
    
}
