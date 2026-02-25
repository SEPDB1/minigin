#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
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

		//static glm::mat3x3  CreateTranslationMatrix(float x, float y, float z = 0.f);
		//static glm::mat3x3 CreateTranslationMatrix(const glm::vec3& translation);

	private:
		glm::vec3 m_Position{};
		//glm::mat3x3 m_Matrix{};
	};
}
