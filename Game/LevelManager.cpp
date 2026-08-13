#include "LevelManager.h"
#include "MiniginEngine.h"
#include "Level.h"

const std::array<std::string, 3> dae::LevelManager::m_LevelNames{ "", "", "" };

dae::LevelManager::LevelManager(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pLevel{ std::make_unique<Level>() }
{

}

dae::LevelManager::~LevelManager() = default;
