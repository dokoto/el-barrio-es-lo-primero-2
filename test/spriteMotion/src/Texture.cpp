#include "Texture.hpp"

namespace barrio {
    
    Texture::Texture() :
    texture(NULL),
    width(0),
    height(0)
    {
        
    }
    
    Texture::~Texture()
    {
        destroy();
    }
    
    bool Texture::loadFromFile(const std::string& path, SDL_Renderer*& renderer)
    {
        destroy();
        
        SDL_Texture* newTexture = NULL;
        
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
            
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == NULL )
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
        if( texture != NULL )
        {
            SDL_DestroyTexture( texture );
            texture = NULL;
            width = 0;
            height = 0;
        }
    }
    
    void Texture::render(const int x, const int y, SDL_Renderer*& renderer, SDL_Rect* clip)
    {
        SDL_Rect renderQuad = { x, y, width, height };
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        
        SDL_RenderCopy( renderer, texture, clip, &renderQuad );
    }
    
    
}

