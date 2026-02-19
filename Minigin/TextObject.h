#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public GameObject
	{
	public:
		TextObject(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);

	private:
		bool m_NeedsUpdate{};
		std::string m_Text{};
		SDL_Color m_Color{ 255, 255, 255, 255 };
		std::shared_ptr<Transform> m_pTransform{};
		std::shared_ptr<Font> m_pFont{};
		std::shared_ptr<Texture2D> m_pTextTexture{};
	};
}
