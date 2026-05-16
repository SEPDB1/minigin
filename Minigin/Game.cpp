#include "Game.h"
#include <algorithm>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "RotaterComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Gamepad.h"

dae::Game::Game(Scene* pScene)
	: m_pScene{ pScene }
{

}


void dae::Game::Start()
{
	auto go = std::make_unique<dae::GameObject>();
	go->AttachComponent<dae::RenderComponent>(go.get())->LoadTexture("background.png");
	m_pBackground = go.get();
	m_pScene->Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(glm::vec3(358, 180, 0.f));
	go->AttachComponent<dae::RenderComponent>(go.get())->LoadTexture("logo.png");
	m_pLogo = go.get();
	m_pScene->Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<dae::GameObject>();
	go->SetPosition(glm::vec2(292, 20));
	go->AttachComponent<dae::TextComponent>(go.get())->SetText("Programming 4 Assignment", font).SetColor({ 255, 255, 0, 255 });
	m_pTitle = go.get();
	m_pScene->Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto pTextO = go->AttachComponent<dae::TextComponent>(go.get());
	pTextO->SetText("FPS", font).SetColor({ 255, 255, 0, 255 });
	go->AttachComponent<dae::FpsComponent>(go.get())->SetTextComponent(pTextO);
	m_pFpsObject = go.get();
	m_pScene->Add(std::move(go));

	// center
	//go = std::make_unique<dae::GameObject>();
	//go->SetPosition(glm::vec2(358, 180));
	//
	//auto player1 = std::make_unique<dae::GameObject>();
	//player1->SetPosition(glm::vec2(-50, -50)).AttachComponent<dae::RenderComponent>(player1.get())->LoadTexture("logo.png");
	//player1->SetParent(go.get(), false).AttachComponent<dae::RotaterComponent>(player1.get())->SetRotationSpeed(1.f);
	//scene.Add(std::move(go));
	//scene.Add(std::move(player1));

	//auto& inputManager{ InputManager::GetInstance() };
	//InputDeviceID gamepadID{ inputManager.CreateNewDevice(std::make_unique<Gamepad>()) };
}

void dae::Game::Update()
{

}