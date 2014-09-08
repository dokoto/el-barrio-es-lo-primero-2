#ifndef __EL_BARRIO_ES_LO_PRIMERO__TEXT__
#define __EL_BARRIO_ES_LO_PRIMERO__TEXT__

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace barrio {
    
    class Text
    {
        
    public:
        Text(void) {}
        ~Text(void);
        void CreateText(const std::string& fontName, const std::string& fontPath, const int fontSize);
        bool renderText(const std::string& fontName, const std::string text, SDL_Color textColor, SDL_Renderer*& renderer);
        SDL_Texture* getTexture(void){ return texture; }
        
        int getPixelWidth() const { return this->pixelWidth; }
        int getPixelHeight() const { return this->pixelHeight; }

    private:
        Text(const Text&){}
        Text& operator=(const Text&);
                
    private:
        std::map<std::string, TTF_Font*> fonts;
        SDL_Texture* texture;
        int pixelWidth;
        int pixelHeight;
        
        void destroy(void);
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__TEXT__) */
