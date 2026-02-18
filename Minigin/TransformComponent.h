#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		const glm::vec3& GetPosition() const;

		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);

	private:
		glm::vec3 m_Position{};
	};
}
