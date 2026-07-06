#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform() = default;
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::mat3x3 GetMatrix() const;
		glm::vec2 GetPosition() const;
		float GetRotation() const;
		glm::vec2 GetScale() const;
		glm::mat3x3 Inversed() const;

		void SetMatrix(const glm::mat3x3& matrix);
		void SetPosition(const glm::vec2& position);
		void SetRotation(float radians);
		void SetScale(const glm::vec2& scale);

	private:
		glm::mat3x3 CreateTranslationMatrix() const;
		glm::mat3x3 CreateRotationMatrix() const;
		glm::mat3x3 CreateScaleMatrix() const;
		void UpdateMatrix() const;

		mutable glm::mat3x3 m_Matrix{ 1.f };
		glm::vec2 m_Translation{ 0.f, 0.f };
		glm::vec2 m_Scale{ 1.f, 1.f};
		float m_Rotation{ 0.f };
		mutable bool m_IsMatrixDirty{ false };
	};
}
