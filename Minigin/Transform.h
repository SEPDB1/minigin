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
		glm::vec2 GetScale() const;

		void SetMatrix(const glm::mat3x3& matrix);
		void SetPosition(float pos_x, float pos_y);
		void SetPosition(const glm::vec2& position);
		void SetRotation(float radians);
		void SetScale(const glm::vec2& scale);
		void SetScale(float scale_x, float scale_y);

	private:
		glm::mat3x3 CreateTranslationMatrix() const;
		glm::mat3x3 CreateRotationMatrix() const;
		glm::mat3x3 CreateScaleMatrix() const;
		void UpdateMatrix() const;

		mutable glm::mat3x3 m_Matrix{ 1.f };
		mutable bool m_IsMatrixDirty{ false };
		glm::vec2 m_Scale{ 1.f, 1.f};
		float m_Rotation{ 0.f };
	};
}
