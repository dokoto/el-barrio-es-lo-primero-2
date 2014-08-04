
#ifndef __EL_BARRIO_ES_LO_PRIMERO__Texture__
#define __EL_BARRIO_ES_LO_PRIMERO__Texture__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace barrio {
    
    class Texture
    {
    public:
        Texture(void);
        virtual ~Texture(void);
        
        bool loadFromFile(const std::string& path, SDL_Renderer*& renderer );
        
        void destroy(void);
        
        void setColor(const Uint8 red, const Uint8 green, const Uint8 blue )
        {
            SDL_SetTextureColorMod( texture, red, green, blue );
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
        
    private:
        SDL_Texture* texture;
        int pixelWidth;
        int pixelHeight;
        
    public:
        int getPixelWidth() const { return this->pixelWidth; }
        void sePixeltWidth(const int pixelWidth) { this->pixelWidth = pixelWidth; }
        
        int getPixelHeight() const { return this->pixelHeight; }
        void setPixelHeight(const int pixelHeight) { this->pixelHeight = pixelHeight; }
        
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Texture__) */
