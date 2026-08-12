#include "Grid.h"
#include "MiniginEngine.h"

dae::Grid::Grid(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_BgObj{ SceneManager::GetInstance().GetActiveScene().AddObject() }
	, m_BgSprite{ m_BgObj.AttachComponent<RenderComponent>() }
{
}

void dae::Grid::Start()
{
	m_BgSprite.LoadTexture("Sprites/Background2.png");
	//m_BgObj.SetScale(glm::vec2(m_Scale * m_TileSize, m_Scale * m_TileSize));
}
