#include "main.hpp"

using namespace std;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
SDL_Surface *message = NULL;
SDL_Color textColor = { 0, 0, 0, 0 };

//The font
TTF_Font *font = NULL;

//The music that will be played
Mix_Music *music = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia(const string&, const string&, const string&);
void close();
void readProperties(const string&);


int main( void )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia("img/4bpp.bmp", "audio/beat.wav", "ttf/lazy.ttf") )
        {
            printf( "Failed to load media!\n" );
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Loading media error\n");
            
        }
        else
        {
            Mix_PlayMusic( music, -1 );
            message = TTF_RenderText_Solid( font, "THIS IS TEXT MESSAGE WITH CUSTOM FONT", textColor );
            
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
            SDL_BlitSurface( message, NULL, gScreenSurface, NULL );
            
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
            
            //Wait two seconds
            SDL_Delay( 5000 );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}


void readProperties(const string& propertiesPath)
{
    Json::Value root;
    Json::Reader reader;
    
    std::ifstream fileDescrip(propertiesPath, ifstream::binary);
    bool parsedSuccess = reader.parse(json_example, root, false);
    
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

bool loadMedia(const string& imgPath, const string& audioPath, const string& ttfPath )
{
    //Load splash image
    gHelloWorld = SDL_LoadBMP( imgPath.c_str() );
    if( gHelloWorld == NULL )
    {
        //printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to load image %s! SDL Error: %s\n", imgPath.c_str(), SDL_GetError());
        return false;
    }
    
    //Open the font
    font = TTF_OpenFont( ttfPath.c_str(), 30 );
    //If there was an error in loading the font
    if( font == NULL )
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Unable to load TTF font %s! SDL Error: %s\n", ttfPath.c_str(), SDL_GetError());
        return false;
    }
    
    //Load the music
    music = Mix_LoadMUS( audioPath.c_str() );
    //If there was a problem loading the music
    if( music == NULL )
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to load sound %s! SDL Error: %s\n", audioPath.c_str(), SDL_GetError());
        return false;
    }
    
    return true;
}

bool init()
{
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL is initilizing...");
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_ERROR, "SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "SDL Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
        
        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            return false;
        }
        
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            return false;
        }
        
    }

    return true;
}