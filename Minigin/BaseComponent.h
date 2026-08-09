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

		virtual void Start() {}
		virtual void Render() const = 0;
		virtual void Update() = 0;

		GameObject* GetOwner() const;

	private:
		GameObject* m_pOwner;
	};
}