#include "Texture.hpp"

namespace barrio {
    
    Texture::Texture(void) :
    texture{nullptr},
    width{0},
    height{0}
    {
        
    }
    
    Texture::~Texture(void)
    {
        destroy();
    }
    
    bool Texture::loadFromFile(const std::string& path, SDL_Renderer*& renderer)
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
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
            
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == nullptr )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to create texture from %s! SDL Error: %s\n",
                               path.c_str(), SDL_GetError() );
            }
            else
            {
                width = loadedSurface->w;
                height = loadedSurface->h;
            }
            
            SDL_FreeSurface( loadedSurface );
        }
        
        texture = newTexture;
        return texture != NULL;
    }
    
    void Texture::destroy(void)
    {
        if( texture != nullptr )
        {
            SDL_DestroyTexture( texture );
            texture = nullptr;
            width = 0;
            height = 0;
        }
    }
    
}

