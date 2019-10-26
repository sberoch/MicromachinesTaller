#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>


class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
public:
    SdlTexture() {}
    SdlTexture(const SdlWindow& window);
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    SdlTexture(const std::string &filename, const SdlWindow& window);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlTexture();
    /**
     * Renderiza la textura cargada
     **/
    int render(const Area& src, const Area& dest) const;
    int render(const Area& src, const Area& dest, double grados, SDL_RendererFlip flip) const;
    /**
     * Asigna una opacidad a la textura
     **/
    void setOpacity(const float opacity);

    //Asigna un color para agregar a la textura
    void setColor(int r, int g, int b);
private:
    SDL_Texture* loadTexture(const std::string &filename);
protected:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif
