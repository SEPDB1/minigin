#pragma once
#include "BaseComponent.h"
#include "Timer.h"

namespace dae
{
	class GameObject;
	class TextComponent;
	class FpsComponent final : public BaseComponent
	{
	public:
		FpsComponent(GameObject* pOwner);
		~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		void SetTextComponent(TextComponent* pTextComponent);

	private:
		TextComponent* m_pTextComponent;
		Timer& m_Timer;
		bool m_NeedsToUpdate;
		float m_AccuTime;
	};
}