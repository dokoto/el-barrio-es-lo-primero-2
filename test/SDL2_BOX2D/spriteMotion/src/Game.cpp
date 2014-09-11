#include "Game.hpp"
#include <stdexcept>
#include <sstream>
#include "ErrorsCodes.hpp"
#include "Colors.hpp"
#include "Clip.hpp"
#include "Measures.hpp"
#include "Flags.hpp"


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
            
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, measure::CAMERA_WIDTH_PX, measure::CAMERA_HEIGHT_PX, SDL_WINDOW_SHOWN );
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
                    
                    physicsWorld.CreateWorld(b2Vec2{0.0f, 0.0f}, Size<int> {measure::WORLD_WIDTH_PX , measure::WORLD_HEIGHT_PX});
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Physics world initializated in [%d, %d] pixel",
                                   measure::WORLD_WIDTH_PX , measure::WORLD_HEIGHT_PX);
                    
                    camera.CreateCamera(SDL_Point{0 ,0}, Size<int>{measure::CAMERA_WIDTH_PX, measure::CAMERA_HEIGHT_PX});
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Camera system initialization in [%d, %d] pixel",
                                   measure::CAMERA_WIDTH_PX, measure::CAMERA_HEIGHT_PX);
                    
                    controller.CreateController(renderer, &physicsWorld, &camera, &texts);
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Controller system initialization...OK");
                    
                    render.CreateRender(renderer, &physicsWorld, &camera, &texts);
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Render system initialization...OK");
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
    
    
    void Game::gameLoop(void)
    {
        bool quitGame = false;
        
        controller.loadLevelWord(LevelsFactory::LEVEL1);
        frameRate.start();
        while (quitGame != flag::QUIT_GAME)
        {
            quitGame = controller.handleSystem();
            //render.drawDebug(frameRate.getFrameRate());
            render.draw();
            controller.releaseClycleLiveTimeResources();
            frameRate.step();
            
        }
    }
}
