#include <SDL3/SDL.h>
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>

dae::Texture2D::Texture2D()
    : m_pTexture{ nullptr }
{

}

dae::Texture2D::Texture2D(SDL_Texture* pTexture)
    : m_pTexture{ nullptr }
{
    SetTexture(pTexture);
}
dae::Texture2D::Texture2D(const std::string& path)
    : m_pTexture{ nullptr }
{
    SetTexture(path);
}

dae::Texture2D::~Texture2D()
{
    DeleteTexture();
}

dae::Texture2D& dae::Texture2D::SetTexture(SDL_Texture* pTexture)
{
    assert(pTexture != nullptr && "Nullptr is an invalid argument");

    DeleteTexture();

    m_pTexture = pTexture;
    return *this;
}

dae::Texture2D& dae::Texture2D::SetTexture(const std::string& path)
{
    const auto fullPath = Renderer::GetInstance().GetPath() / path;
    SDL_Surface* surface = SDL_LoadPNG(fullPath.string().c_str());
    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError());
    }

    DeleteTexture();

    m_pTexture = SDL_CreateTextureFromSurface(
        Renderer::GetInstance().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!m_pTexture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError());
    }
    
    return *this;
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

void dae::Texture2D::DeleteTexture()
{
    if (m_pTexture)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}
