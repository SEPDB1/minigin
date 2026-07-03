// standard includes
#include <stdexcept>
#include <cstring>
#include <iostream>

// library includes
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>

// project includes
#include "Renderer.h"
#include "SceneManager.h"
#include "UiManager.h"

#pragma region SDLRendererImpl

class dae::SDLRenderer::SDLRendererImpl final
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
	SDL_Window* m_pWindow{};
	SDL_Color m_ClearColor{};
	std::filesystem::path m_Path{};
};

void dae::SDLRenderer::SDLRendererImpl::Init(SDL_Window* pWindow)
{
	m_pWindow = pWindow;
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	m_Renderer = SDL_CreateRenderer(pWindow, nullptr);
	if (m_Renderer == nullptr)
	{
		std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
#if __EMSCRIPTEN__
	// For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
	// You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
	io.IniFilename = NULL;
#endif

	ImGui_ImplSDL3_InitForSDLRenderer(pWindow, m_Renderer);
	ImGui_ImplSDLRenderer3_Init(m_Renderer);
}

void dae::SDLRenderer::SDLRendererImpl::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::SDLRenderer::SDLRendererImpl::Destroy()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::SDLRenderer::SDLRendererImpl::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_FRect dst{};
	dst.x = x;
	dst.y = y;
	SDL_GetTextureSize(texture.GetSDLTexture(), &dst.w, &dst.h);
	SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::SDLRenderer::SDLRendererImpl::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_FRect dst{};
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::SDLRenderer::SDLRendererImpl::SetBackgroundColor(const SDL_Color& color)
{
	m_ClearColor = color;
}

SDL_Renderer* dae::SDLRenderer::SDLRendererImpl::GetSDLRenderer() const
{ 
	return m_Renderer; 
}

const SDL_Color& dae::SDLRenderer::SDLRendererImpl::GetBackgroundColor() const
{
	return m_ClearColor;
}

const std::filesystem::path& dae::SDLRenderer::SDLRendererImpl::GetPath() const
{
	return m_Path;
}

#pragma endregion SDLRendererImpl

dae::SDLRenderer::SDLRenderer()
	: m_pSDLRendererImpl{ std::make_unique<SDLRendererImpl>() }
{
}

dae::SDLRenderer::~SDLRenderer() = default;

void dae::SDLRenderer::Init(SDL_Window* pWindow)
{
	m_pSDLRendererImpl->Init(pWindow);
}

void dae::SDLRenderer::Render() const
{
	m_pSDLRendererImpl->Render();
}

void dae::SDLRenderer::Destroy()
{
	m_pSDLRendererImpl->Destroy();
}

void dae::SDLRenderer::RenderTexture(const Texture2D& texture, float x, float y) const
{
	m_pSDLRendererImpl->RenderTexture(texture, x, y);
}

void dae::SDLRenderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const
{
	m_pSDLRendererImpl->RenderTexture(texture, x, y, width, height);
}

void dae::SDLRenderer::SetBackgroundColor(const SDL_Color& color)
{
	m_pSDLRendererImpl->SetBackgroundColor(color);
}

SDL_Renderer* dae::SDLRenderer::GetSDLRenderer() const
{
	return m_pSDLRendererImpl->GetSDLRenderer();
}

const SDL_Color& dae::SDLRenderer::GetBackgroundColor() const
{
	return m_pSDLRendererImpl->GetBackgroundColor();
}

const std::filesystem::path& dae::SDLRenderer::GetPath() const
{
	return m_pSDLRendererImpl->GetPath();
}
