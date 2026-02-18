#pragma once
#include <glm/vec2.hpp>
#include <string>
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();
		TextureComponent(const TextureComponent&) = default;
		TextureComponent(TextureComponent&&) = default;
		TextureComponent& operator=(const TextureComponent&) = default;
		TextureComponent& operator=(TextureComponent&&) = default;

		TextureComponent& SetTexture(SDL_Texture* pTexture);
		TextureComponent& SetTexture(const std::string& path);

		SDL_Texture* GetSDLTexture() const;
		glm::vec2 GetSize() const;

	private:
		SDL_Texture* m_pTexture{};
	};
}
