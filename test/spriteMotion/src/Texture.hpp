
#ifndef __EL_BARRIO_ES_LO_PRIMERO__Texture__
#define __EL_BARRIO_ES_LO_PRIMERO__Texture__

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace barrio {
    
    class Texture
    {
    public:
        Texture();
        virtual ~Texture();
        
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
        
        void render(const int x, const int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL );
        
        int velocityX;
        int velocityY;
        int posX;
        int posY;
        int width;
        int height;
        
    private:
        SDL_Texture* texture;
        
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Texture__) */
