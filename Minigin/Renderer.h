#pragma once
#include <memory>
#include <filesystem>
#include "Singleton.h"

struct SDL_Window;
struct SDL_Color;
struct SDL_Renderer;

namespace dae
{
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Texture2D;
	class Transform;
	class SDLRenderer final : public Singleton<SDLRenderer>
	{
	public:
		SDLRenderer();
		~SDLRenderer();
		SDLRenderer(const SDLRenderer& other) = delete;
		SDLRenderer(SDLRenderer&& other) = delete;
		SDLRenderer& operator=(const SDLRenderer& other) = delete;
		SDLRenderer& operator=(SDLRenderer&& other) = delete;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const Transform& transform) const;

		void SetBackgroundColor(const SDL_Color& color);

		SDL_Renderer* GetSDLRenderer() const;
		const SDL_Color& GetBackgroundColor() const;
		const std::filesystem::path& GetPath() const;

	private:
		class SDLRendererImpl;
		std::unique_ptr<SDLRendererImpl> m_pSDLRendererImpl{};
	};
}

