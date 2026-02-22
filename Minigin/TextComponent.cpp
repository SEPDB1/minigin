#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"

dae::TextComponent::TextComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{

}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Text.length(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_pTextTexture = std::make_unique<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

dae::TextComponent& dae::TextComponent::SetText(const std::string & text, std::shared_ptr<Font> font, const SDL_Color & color)
{
	m_NeedsUpdate = true;
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

	m_NeedsUpdate = true;
	m_Text = text;
	return *this;
}

dae::TextComponent& dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
	return *this;
}

dae::Texture2D* dae::TextComponent::GetTexture() const
{
	return m_pTextTexture.get();
}