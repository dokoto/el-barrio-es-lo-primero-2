
#ifndef __EL_BARRIO_ES_LO_PRIMERO__Texture__
#define __EL_BARRIO_ES_LO_PRIMERO__Texture__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>

#include "Measures.hpp"
#include "Glob.hpp"

namespace barrio {
    
    class Texture
    {
    public:        
        Texture(void);
        virtual ~Texture(void);
        virtual bool amTexture(void) { return true; }
        
        void destroy(void);
        
        void setColor(const Uint8 red, const Uint8 green, const Uint8 blue )
        {
            SDL_SetTextureColorMod( texture, red, green, blue );
        }
        
        void setTransparentColor(SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0})
        {
            this->transparentColor = transparentColor;
        }
        
        void setBlendMode( SDL_BlendMode blending )
        {
            SDL_SetTextureBlendMode( texture, blending );
        }
        
        void setAlpha(const Uint8 alpha )
        {
            SDL_SetTextureAlphaMod( texture, alpha );
        }                
        
        SDL_Texture* getSDLTexture()
        {
            return texture;
        }
        
        bool isEmpty()
        {
            return texture == nullptr;
        }
        
        SDL_Texture* getTexture(void)
        {
            return texture;
        }
        
        virtual void setSide(Glob::Side side){ this->side = side; }
        virtual bool getSide(void) const { return this->side; }
        virtual Glob::Classes whoAmI(void) { return Glob::Classes::TEXTURE; }
        
        bool loadFromFile(const std::string& path, SDL_Renderer*& renderer, const double zoomX = 1.0, const double zoomY = 1.0);
        
    private:
        SDL_Texture* texture;
        SDL_Color transparentColor;
        int pixelWidth;
        int pixelHeight;
        Glob::Side side;
                
    public:
        int getPixelWidth() const { return this->pixelWidth; }
        void sePixelWidth(const int pixelWidth) { this->pixelWidth = pixelWidth; }
        
        int getPixelHeight() const { return this->pixelHeight; }
        void setPixelHeight(const int pixelHeight) { this->pixelHeight = pixelHeight; }
        
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Texture__) */
