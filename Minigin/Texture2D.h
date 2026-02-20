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
	class Texture2D final
	{
	public:
		Texture2D();
		explicit Texture2D(SDL_Texture* pTexture);
		explicit Texture2D(const std::string& path);
		~Texture2D();
		Texture2D(const Texture2D&) = default;
		Texture2D(Texture2D&&) = default;
		Texture2D& operator=(const Texture2D&) = default;
		Texture2D& operator=(Texture2D&&) = default;

		Texture2D& SetTexture(SDL_Texture* pTexture);
		Texture2D& SetTexture(const std::string& path);

		SDL_Texture* GetSDLTexture() const;
		glm::vec2 GetSize() const;

	private:
		void DeleteTexture();
		SDL_Texture* m_pTexture{};
	};
}
