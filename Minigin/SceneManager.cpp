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
	m_pActiveScene->Update();
}

void dae::SceneManager::Render()
{
	m_pActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_pScenes.emplace_back(new Scene());
	return *m_pScenes.back();
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{
	return *m_pActiveScene;
}

void dae::SceneManager::SetActiveScene(Scene& scene)
{
	m_pActiveScene = std::addressof(scene);
}

dae::SceneManager::SceneManager()
	: m_pScenes{}
	, m_pActiveScene{}
{
	CreateScene();
	m_pActiveScene = m_pScenes.back().get();
}