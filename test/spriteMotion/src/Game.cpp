#include "Game.hpp"


#include <stdexcept>
#include "errorsCodes.hpp"


namespace barrio {
    
    using namespace std;
    
    Game::Game() :
    
        window{nullptr},
        renderer{nullptr},
        physicsWorld{nullptr},
        camera(nullptr),
        player(nullptr)
    
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
            
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CAMERA_WIDTH, CAMERA_HEIGHT, SDL_WINDOW_SHOWN );
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
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "SDL2 image system is initilization...OK");
                    physicsWorld = new Physics(b2Vec2{0.0f, 0.0f}, WORLD_WIDTH, WORLD_HEIGHT);
                    camera = new unique_ptr<Camera>(CAMERA_WIDTH, CAMERA_HEIGHT, WORLD_WIDTH, WORLD_HEIGHT);
                }
            }
        }
    }
    
    Game::~Game()
    {
        //Destroy Physics World
        if(physicsWorld != nullptr)
        {
            delete physicsWorld;
            physicsWorld = nullptr;
        }
        
        if (camera != nullptr)
        {
            delete camera;
            camera = nullptr;
        }
        
        if (player != nullptr)
        {
            player = nullptr;
        }
        
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
        camera->setBackground("img/backgorund_1679x600.png", renderer);
        player = new Character("player", renderer);
        player->loadAnimations("conf/spriteSheets/player.json", "img/foo.png");
        player->addToPhysicsWorld(physicsWorld, 5.0f, -1.5f);
        camera->follow(player);
    }
    
    void Game::gameLoop(void)
    {
        bool quit = false;
        SDL_Event e;
        loadMedia();
                
        player->setVelocity(b2Vec2{-0.5f, 0.0f});
        
        while (quit == false)
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }
            physicsWorld->Step();
            SDL_SetRenderDrawColor( renderer, color::WHITE, color::WHITE, color::WHITE, color::WHITE );
            SDL_RenderClear( renderer );
            
            camera->renderBackGround(renderer);
            camera->renderAnimation(player->playAnimation("walking", 10), renderer, player);
            
            SDL_RenderPresent( renderer );
        }
    }
    
}
