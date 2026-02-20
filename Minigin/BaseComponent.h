#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner);
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;

		virtual void Update() = 0;

	protected:
		GameObject* GetOwner() const;

	private:
		GameObject* const m_pOwner;
	};
}