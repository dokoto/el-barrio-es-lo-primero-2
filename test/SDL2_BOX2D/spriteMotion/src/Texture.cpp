#include "Texture.hpp"

namespace barrio {
    
    Texture::Texture(void) :
    texture{nullptr},
    pixelWidth{0},
    pixelHeight{0},
    side{Glob::Side::RIGHT_SIDE}
    {
        
    }
    
    Texture::~Texture(void)
    {
        destroy();
    }
    
    bool Texture::loadFromFile(const std::string& path, SDL_Renderer*& renderer, const double zoomX, const double zoomY)
    {
        destroy();
        
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == nullptr )
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            if (zoomX != 1 && zoomY != 1)
            {
                SDL_Surface* zoomedSurface = zoomSurface( loadedSurface, zoomX, zoomY, SMOOTHING_OFF );
                if (zoomedSurface != nullptr)
                {
                    SDL_FreeSurface( loadedSurface );
                    loadedSurface = nullptr;
                    loadedSurface = zoomedSurface;
                }
                else
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_WARN, "Unable to resize image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
                }
            }
            
            if (SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, transparentColor.r, transparentColor.g, transparentColor.b ) ) != 0)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_WARN, "Unable to set transparent color.");
            }
            
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == nullptr )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to create texture from %s! SDL Error: %s\n",
                               path.c_str(), SDL_GetError() );
            }
            else
            {
                pixelWidth = loadedSurface->w;
                pixelHeight = loadedSurface->h;
            }
            
            SDL_FreeSurface( loadedSurface );
            loadedSurface = nullptr;
        }
        
        texture = newTexture;
        return texture != NULL;
    }
    
    void Texture::destroy(void)
    {
        if( texture != nullptr )
        {
            printf("Destroing Texture\n");
            SDL_DestroyTexture( texture );
            texture = nullptr;
            pixelWidth = 0;
            pixelHeight = 0;            
        }
    }
    
}

