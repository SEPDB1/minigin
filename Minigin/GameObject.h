#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;
	class GameObject 
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		// Creates a new component instance and attaches it to the game object,
		// the template type has to be a component type
		template <typename T>
		std::shared_ptr<T> AttachComponent()
		{
			auto comp = std::make_shared<T>();
			m_Components.push_back(comp);
			return comp;
		}

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
	};
}
