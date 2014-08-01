
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
        
        void render(const int x, const int y, SDL_Renderer*& renderer, SDL_Rect* clip = nullptr );        
        
        
    private:
        SDL_Texture* texture;
        int width;
        int height;        
        
    public:
        int getWidth() const { return this->width; }
        void setWidth(const int width){ this->width = width; }
        
        int getHeight() const { return this->height; }
        void setHeight(const int height){ this->height = height; }
        
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Texture__) */
