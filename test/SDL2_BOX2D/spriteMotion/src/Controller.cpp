#include "Controller.hpp"
#include "ErrorsCodes.hpp"
#include "Flags.hpp"
#include "Measures.hpp"

namespace barrio {
    
    void Controller::CreateController(SDL_Renderer*& renderer, Physics* physicsWorld, Camera* camera, Text* texts)
    {
        this->renderer = renderer;
        this->physicsWorld = physicsWorld;
        this->camera = camera;
        this->texts = texts;
    }
    
    void Controller::loadLevelWord(const LevelsFactory::Stage stage)
    {
        currentLevel = levelFactory.CreateIntance(stage);
        currentLevel->CreateLevel(renderer, physicsWorld, camera, texts);
        currentLevel->loadLevelWorld();
    }
    
    bool Controller::handleSystem(void)
    {
        if (handleGameState(&event) == flag::QUIT_GAME)
        {
            return flag::QUIT_GAME;
        }
        else
        {
            currentLevel->handleInput();
            currentLevel->IA();
            return flag::CONTINUE_GAME;
        }
    }
    
    void Controller::releaseClycleLiveTimeResources()
    {
        currentLevel->releaseClycleLiveTimeResources();
    }
    
    Controller::~Controller(void)
    {
        if (currentLevel != nullptr)
        {
            delete currentLevel;
        }
    }
    
    
    bool Controller::handleGameState(SDL_Event* event)
    {
        bool quit = flag::CONTINUE_GAME;
        static Uint32 ms = 0;
        while( SDL_PollEvent( event ) != 0 )
        {
            if( event->type == SDL_QUIT )
            {
                quit = flag::QUIT_GAME;
            }
            else if ( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
            {
                quit = flag::QUIT_GAME;
            }
            else if( event->type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Mouse click position: [%d, %d]", camera->cameraPosition.x + event->button.x, event->button.y);
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
                            ms = measure::RESUME_STATE_DELAY_IN_MS;
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
                            ms = measure::RESUME_STATE_DELAY_IN_MS;
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
                            ms = measure::RESUME_STATE_DELAY_IN_MS;
                            break;
                        case SDL_WINDOWEVENT_CLOSE:
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE, "Window %d closed", event->window.windowID);
                            ms = measure::RESUME_STATE_DELAY_IN_MS;
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

