#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform();
		~Transform();
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetPosition() const;

		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);

	private:
		glm::vec3 m_Position{};
	};
}
