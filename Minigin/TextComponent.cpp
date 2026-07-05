#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Timer.h"

const float dae::TextComponent::m_UpdateTime{ 0.1f };

dae::TextComponent::TextComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{

}

void dae::TextComponent::Render() const
{
	SDLRenderer::GetInstance().RenderTexture(*m_pTextTexture, BaseComponent::GetOwner()->GetTransform());
}

void dae::TextComponent::Update()
{
	if (m_TextChanged && m_ShouldUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Text.length(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(SDLRenderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_pTextTexture = std::make_unique<Texture2D>(texture);
		m_TextChanged = false;
		m_ShouldUpdate = false;
	}
	else if (!m_ShouldUpdate)
	{
		m_ElapsedTime += Timer::GetInstance().GetElapsedTime();

		if (m_ElapsedTime >= m_UpdateTime)
		{
			m_ElapsedTime = 0.f;
			m_ShouldUpdate = true;
		}
	}
}

dae::TextComponent& dae::TextComponent::SetText(const std::string & text, std::shared_ptr<Font> font, const SDL_Color & color)
{
	m_TextChanged = true;
	m_Text = text;
	m_pFont = std::move(font);
	m_Color = color;
	return *this;
}

dae::TextComponent& dae::TextComponent::SetText(const std::string& text)
{
	// Assume that the user made a mistake if font is still null (should call overload of SetText instead)
	if (!m_pFont)
	{
		throw std::runtime_error(std::string("Font is a nullptr"));
	}

	m_TextChanged = true;
	m_Text = text;
	return *this;
}

dae::TextComponent& dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_TextChanged = true;
	return *this;
}

dae::Texture2D* dae::TextComponent::GetTexture() const
{
	return m_pTextTexture.get();
}