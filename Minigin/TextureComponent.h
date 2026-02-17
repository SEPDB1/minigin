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
	class TextureComponent : public BaseComponent
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit TextureComponent(SDL_Texture* texture);
		explicit TextureComponent(const std::string& fullPath);
		~TextureComponent();

		glm::vec2 GetSize() const;

		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;
	private:
		SDL_Texture* m_Texture;
	};
}
