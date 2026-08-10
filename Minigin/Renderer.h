#pragma once
#include <memory>
#include <filesystem>
#include "Singleton.h"
#include <glm/vec2.hpp>

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
	struct Rect;
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

		void RenderTexture(const Texture2D& texture, const Transform& transform, const glm::vec2& offset = glm::vec2(0.f, 0.f)) const;

		void SetBackgroundColor(const SDL_Color& color);

		SDL_Renderer* GetSDLRenderer() const;
		const SDL_Color& GetBackgroundColor() const;
		const std::filesystem::path& GetPath() const;
		Rect GetScreenBounds() const;

	private:
		class SDLRendererImpl;
		std::unique_ptr<SDLRendererImpl> m_pSDLRendererImpl{};
	};
}

