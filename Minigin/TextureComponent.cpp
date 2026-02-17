#include <SDL3/SDL.h>
#include "TextureComponent.h"
#include "Renderer.h"
#include <stdexcept>

dae::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_Texture);
}

glm::vec2 dae::TextureComponent::GetSize() const
{
    float w{}, h{};
    SDL_GetTextureSize(m_Texture, &w, &h);
    return { w, h };
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}

dae::TextureComponent::TextureComponent(const std::string &fullPath)
{
    SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError()
        );
    }

    m_Texture = SDL_CreateTextureFromSurface(
        Renderer::GetInstance().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!m_Texture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError()
        );
    }
}

dae::TextureComponent::TextureComponent(SDL_Texture* texture)	: m_Texture{ texture } 
{
	assert(m_Texture != nullptr);
}

