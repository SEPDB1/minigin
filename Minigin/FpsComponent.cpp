#include "FpsComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iomanip>
#include <sstream>

dae::FpsComponent::FpsComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_pTextComponent{ nullptr }
	, m_Timer{ dae::Timer::GetInstance() }
	, m_NeedsToUpdate{ true }
	, m_AccuTime{ 0.9f } // force early update
{

}

void dae::FpsComponent::Render() const
{
	const auto& pos = BaseComponent::GetOwner()->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTextComponent->GetTexture(), pos.x, pos.y);
}

void dae::FpsComponent::Update()
{
	m_AccuTime += m_Timer.GetElapsedTime();
	if (m_AccuTime >= 1.f)
	{
		m_AccuTime = 0.f;
		m_NeedsToUpdate = true;
	}

	if (m_NeedsToUpdate && m_pTextComponent)
	{
		const float Fps = m_Timer.GetFps();
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << Fps;
		m_pTextComponent->SetText(stream.str() + " FPS");
		m_NeedsToUpdate = false;
	}
}

void dae::FpsComponent::SetTextComponent(TextComponent* pTextComponent)
{
	m_pTextComponent = pTextComponent;
}