#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Start()
{
	for (auto& pScene : m_pScenes)
	{
		pScene->Start();
	}
}

void dae::SceneManager::Update()
{
	for(auto& pScene : m_pScenes)
	{
		pScene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& pScene : m_pScenes)
	{
		pScene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	//m_pScenes.emplace_back(std::make_unique<Scene>());
	m_pScenes.emplace_back(new Scene());
	return *m_pScenes.back();
}
