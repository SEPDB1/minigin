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

		const glm::mat3x3 GetMatrix() const;
		glm::vec2 GetPosition() const;
		float GetRotation() const;

		void SetMatrix(const glm::mat3x3& matrix);
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);
		void SetRotation(float radians);

	private:
		static glm::mat3x3 CreateTranslationMatrix(float x, float y);
		static glm::mat3x3 CreateTranslationMatrix(const glm::vec2& translation);
		// Returns a rotation matrix around the Z axis
		static glm::mat3x3 CreateRotationMatrix(float radians);
		static glm::mat3x3 CreateScaleMatrix(float x, float y);
		static glm::mat3x3 CreateScaleMatrix(const glm::vec2& scale);

		glm::mat3x3 m_Matrix{};
		float m_Rotation{ 0.f };
	};
}
