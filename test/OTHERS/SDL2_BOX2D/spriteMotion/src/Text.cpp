#include "Text.hpp"

namespace barrio {
    
    void Text::CreateText(const std::string& fontName, const std::string& fontPath, const int fontSize)
    {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (font == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_ERROR, "Unable to load font %s! SDL_image Error: %s\n", fontPath.c_str(), TTF_GetError());
        }
        fonts.insert(std::make_pair(fontName, font));
    }
    
    
    Text::~Text(void)
    {
        destroy();
        for (auto it = fonts.begin(); it != fonts.end(); it++)
        {
            if (it->second != nullptr)
            {
                TTF_CloseFont(it->second);
            }
        }
        
    }
    
    bool Text::renderText(const std::string& fontName, const std::string text, SDL_Color textColor, SDL_Renderer*& renderer)
    {
        destroy();
        //Render text surface
        auto it = fonts.find(fontName);
        if (it != fonts.end())
        {
            SDL_Surface* textSurface = TTF_RenderText_Solid( it->second, text.c_str(), textColor );
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
        }
        
        return texture != NULL;
    }
    
    void Text::destroy(void)
    {
        if( texture != nullptr )
        {
            SDL_DestroyTexture( texture );
            texture = nullptr;
            pixelWidth = 0;
            pixelHeight = 0;
        }
    }
    
}
