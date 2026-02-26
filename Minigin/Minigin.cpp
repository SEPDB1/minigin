#include <stdexcept>
#include <sstream>
#include <iostream>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "RotaterComponent.h"

SDL_Window* g_window{};

void LogSDLVersion(const std::string& message, int major, int minor, int patch)
{
#if WIN32
	std::stringstream ss;
	ss << message << major << "." << minor << "." << patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << major << "." << minor << "." << patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	static_cast<dae::Minigin*>(arg)->Update();
}
#endif

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	LogSDLVersion("Compiled with SDL", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
	int version = SDL_GetVersion();
	LogSDLVersion("Linked with SDL ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));

	LogSDLVersion("Compiled with SDL_ttf ",	SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION,SDL_TTF_MICRO_VERSION);
	version = TTF_Version();
	LogSDLVersion("Linked with SDL_ttf ", SDL_VERSIONNUM_MAJOR(version), SDL_VERSIONNUM_MINOR(version),	SDL_VERSIONNUM_MICRO(version));
}

dae::Minigin::Minigin(const std::filesystem::path& dataPath)
{
	PrintSDLVersion();
	
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		SDL_Log("Renderer error: %s", SDL_GetError());
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		1024,
		576,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window, dataPath);
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();
	Start();
#ifndef __EMSCRIPTEN__
	while (!m_quit)
		Update();
#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}

void dae::Minigin::Start()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->AttachComponent<dae::RenderComponent>(go.get())->LoadTexture("background.png");
	m_pBackground = go.get();
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	//go->SetPosition(358, 180);
	go->SetPosition(glm::vec3(358, 180, 0.f));
	go->AttachComponent<dae::RenderComponent>(go.get())->LoadTexture("logo.png");
	m_pLogo = go.get();
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<dae::GameObject>();
	//go->SetPosition(292, 20);
	go->SetPosition(glm::vec3(292, 20, 0.f));
	go->AttachComponent<dae::TextComponent>(go.get())->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	//go->SetParent(m_pLogo, true);
	m_pTitle = go.get();
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto pTextO = go->AttachComponent<dae::TextComponent>(go.get());
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	go->AttachComponent<dae::FpsComponent>(go.get())->SetTextComponent(pTextO);
	m_pFpsObject = go.get();
	scene.Add(std::move(go));

	// center
	//go = std::make_unique<dae::GameObject>();
	//go->SetPosition(glm::vec3(358, 180, 0.f));
	//
	//auto player1 = std::make_unique<dae::GameObject>();
	//player1->SetPosition(glm::vec3(378, 180, 0.f));
	//player1->AttachComponent<dae::RenderComponent>(go.get())->LoadTexture("logo.png");
	//player1->SetParent(go.get(), true).AttachComponent<dae::RotaterComponent>(player1.get());
	//scene.Add(std::move(go));
	//scene.Add(std::move(player1));
}

void dae::Minigin::Update()
{
	//const glm::vec3 startPos{ 358.f, 180.f, 0.f };
	//const glm::vec3 endPos{ startPos.x + 100.f, startPos.y + 100.f, 0.f };

	//auto lerp = [](const glm::vec3& currentPos, const glm::vec3& desiredPos, float t)
	//	{ return currentPos * (1 - t) + desiredPos * t;  };

	//m_pLogo->SetPosition(lerp(m_pLogo->GetLocalPosition(), endPos, Timer::GetInstance().GetElapsedTime()));

	m_quit = !InputManager::GetInstance().ProcessInput();
	SceneManager::GetInstance().Update();
	Timer::GetInstance().Update();
	Renderer::GetInstance().Render();
}
