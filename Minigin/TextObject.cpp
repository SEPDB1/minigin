#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"

dae::TextObject::TextObject(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Color(color)
	, m_pTransform(GameObject::AttachComponent<TransformComponent>())
	, m_pFont(std::move(font))
	, m_pTextTexture()
{
}

void dae::TextObject::Update()
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
		m_pTextTexture = std::make_shared<TextureComponent>();
		m_pTextTexture->SetTexture(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextObject::Render() const
{
	if (m_pTextTexture != nullptr)
	{
		const auto& pos = m_pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void dae::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_pTransform->SetPosition(x, y);
}

void dae::TextObject::SetColor(const SDL_Color& color) 
{ 
	m_Color = color; 
	m_NeedsUpdate = true; 
}


