#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include <SDL3/SDL_pixels.h>

namespace dae
{
	class GameObject;
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pOwner);
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		TextComponent& SetText(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
		TextComponent& SetText(const std::string& text);
		TextComponent& SetColor(const SDL_Color& color);

		Texture2D* GetTexture() const;

	private:
		bool m_NeedsUpdate{};
		std::string m_Text{};
		SDL_Color m_Color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_pFont{};
		std::unique_ptr<Texture2D> m_pTextTexture{};
	};
}