#ifndef __EL_BARRIO_ES_LO_PRIMERO__DebugInfo__
#define __EL_BARRIO_ES_LO_PRIMERO__DebugInfo__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace barrio {
    
    class DebugInfo
    {
        
    public:
        DebugInfo(void) : font { nullptr } {}
        ~DebugInfo(void);
        void CreateDebugInfo(const std::string& fontPath, const int fontSize);
        bool writeText(const std::string text, SDL_Color textColor, SDL_Renderer*& renderer);
        SDL_Texture* getTexture(void){ return texture; }
        
        int getPixelWidth() const { return this->pixelWidth; }
        void sePixeltWidth(const int pixelWidth) { this->pixelWidth = pixelWidth; }
        
        int getPixelHeight() const { return this->pixelHeight; }
        void setPixelHeight(const int pixelHeight) { this->pixelHeight = pixelHeight; }
        
    private:
        TTF_Font* font;
        SDL_Texture* texture;
        int pixelWidth;
        int pixelHeight;
        
        void destroy(void);
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__DebugInfo__) */
