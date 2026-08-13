#include "Enemies.h"
#include "MiniginEngine.h"

dae::EnemyComponent::EnemyComponent(GameObject* pOwner, const std::string& pathSprite, float movementSpeed)
	: BaseComponent(pOwner)
	, m_Sprite{ pOwner->AttachComponent<RenderComponent>() }
	, m_Hitbox{ pOwner->AttachComponent<HitboxComponent>(16.f, 16.f, false) }
	, m_MovementSpeed{ movementSpeed }
{
	m_Sprite.LoadTexture(pathSprite);
	pOwner->SetScale(glm::vec2(m_SpriteScale, m_SpriteScale));
}

dae::EnemyTank::EnemyTank(GameObject* pOwner, const glm::vec2& pos)
	: EnemyComponent(pOwner, "Sprites/EnemyTank.png", m_MovementSpeed)
{
	pOwner->SetPosition(pos);
}

dae::Recognizer::Recognizer(GameObject* pOwner, const glm::vec2& pos)
	: EnemyComponent(pOwner, "Sprites/Recognizer.png", m_MovementSpeed)
{
	pOwner->SetPosition(pos);
}
