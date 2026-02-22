#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FpsComponent.h"
//#include "Test.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->AttachComponent<dae::RenderComponent>(go.get())->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(358, 180);
	go->AttachComponent<dae::RenderComponent>(go.get())->SetTexture("logo.png");
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<dae::GameObject>();
	go->SetPosition(292, 20);
	go->AttachComponent<dae::TextComponent>(go.get())->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto pTextO = go->AttachComponent<dae::TextComponent>(go.get());
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	go->AttachComponent<dae::FpsComponent>(go.get())->SetTextComponent(pTextO);
	scene.Add(std::move(go));

	// Test
	//dae::test::TestSceneGraph();
	auto pParent = std::make_unique<dae::GameObject>();
	auto pChild = std::make_unique<dae::GameObject>();
}

int main(int, char*[])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
