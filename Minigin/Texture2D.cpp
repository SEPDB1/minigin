#include <SDL3/SDL.h>
#include <stdexcept>
#include "memory.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::Texture2D::Texture2D(const std::string& path)
    : m_pTexture{ LoadTexture(path) }
{
}

dae::Texture2D::Texture2D(SDL_Texture* pTexture)
    : m_pTexture{ pTexture }
{
    assert(pTexture);
}

dae::Texture2D::~Texture2D()
{
    DeleteTexture();
}


SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
    return m_pTexture;
}

glm::vec2 dae::Texture2D::GetSize() const
{
    float w{}, h{};
    SDL_GetTextureSize(m_pTexture, &w, &h);
    return { w, h };
}

SDL_Texture* dae::Texture2D::LoadTexture(const std::string& path)
{
    SDL_Surface* surface = SDL_LoadPNG(path.c_str());
    SDL_Texture* pTexture{};

    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError());
    }

    DeleteTexture();

    pTexture = SDL_CreateTextureFromSurface(
        Renderer::GetInstance().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!pTexture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError());
    }

    return pTexture;
}

void dae::Texture2D::DeleteTexture()
{
    if (m_pTexture)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}
