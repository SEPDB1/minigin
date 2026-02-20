#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	class GameObject;
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pOwner);
		~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Render() const;
		void Update(float) override;

		RenderComponent& SetTexture(SDL_Texture* pTexture);
		RenderComponent& SetTexture(const std::string& path);

		Texture2D* GetTexture() const;

	private:
		std::unique_ptr<Texture2D> m_pTexture;
	};
}