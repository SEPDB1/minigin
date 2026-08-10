#pragma once

namespace dae
{
	class GameObject;
	struct CollisionInfo;
	class HitboxComponent;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;

		virtual void Start() {}
		virtual void Render() const {}
		virtual void Update() {}
		virtual void OnCollision(const CollisionInfo&) {}

		GameObject* GetOwner() const;

	protected:
		BaseComponent(GameObject* pOwner);

	private:
		GameObject* m_pOwner;
	};
}