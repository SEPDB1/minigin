#pragma once
#include <SDL3/SDL.h>
#include "Singleton.h"
#include <filesystem>

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		void SetBackgroundColor(const SDL_Color& color);

		SDL_Renderer* GetSDLRenderer() const;
		const SDL_Color& GetBackgroundColor() const;
		const std::filesystem::path& GetPath() const;

	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_ClearColor{};
		std::filesystem::path m_Path{};
	};
}

