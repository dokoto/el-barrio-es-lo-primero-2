#include "DebugInfo.hpp"

namespace barrio {
    
    void DebugInfo::CreateDebugInfo(const std::string& fontPath, const int fontSize)
    {
        font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (font == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_ERROR, "Unable to load font %s! SDL_image Error: %s\n", fontPath.c_str(), TTF_GetError());
        }
    }
    
    
    DebugInfo::~DebugInfo(void)
    {
        destroy();
        if (font != nullptr)
        {
            TTF_CloseFont(font);
        }
    }
    
    bool DebugInfo::writeText(const std::string text, SDL_Color textColor, SDL_Renderer*& renderer)
    {
        destroy();
        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
        if( textSurface != NULL )
        {
            //Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface( renderer, textSurface );
            if( texture == NULL )
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_ERROR,  "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                pixelWidth = textSurface->w;
                pixelHeight = textSurface->h;
            }
            
            //Get rid of old surface
            SDL_FreeSurface( textSurface );
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_ERROR, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        
        return texture != NULL;
    }
    
    void DebugInfo::destroy(void)
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
