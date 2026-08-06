#include "Transform.h"

# define PI_F           3.1415926536f
# define PI_F_MUL_2     6.2821853072f

const glm::mat3x3& dae::Transform::GetMatrix() const
{
	if (m_IsMatrixDirty)
		UpdateMatrix();

	return m_Matrix;
}

glm::vec2 dae::Transform::GetPosition() const
{
	return m_Translation;
}

float dae::Transform::GetRotation() const
{
	return m_Rotation;
}

glm::vec2 dae::Transform::GetScale() const
{
	return m_Scale;
}

void dae::Transform::SetMatrix(const glm::mat3x3& matrix)
{
	const float scaleX{ glm::length(glm::vec2(matrix[0][0], matrix[1][0])) };
	const float scaleY{ glm::length(glm::vec2(matrix[0][1], matrix[1][1])) };

	// ✅ translation is in row 2 (index 2) of columns 0 and 1
	m_Translation = { matrix[0][2], matrix[1][2] };

	m_Rotation = std::atan2(matrix[1][0], matrix[0][0]);
	m_Scale = { scaleX, scaleY };
	m_Matrix = matrix;

	m_IsMatrixDirty = false;
}

void dae::Transform::SetPosition(const glm::vec2& position) 
{ 
	m_Translation = position;
	m_IsMatrixDirty = true;
}

void dae::Transform::SetRotation(float radians)
{
	m_Rotation = radians;

	while (m_Rotation > PI_F_MUL_2)
		m_Rotation -= PI_F_MUL_2;

	while (m_Rotation < -PI_F_MUL_2)
		m_Rotation += PI_F_MUL_2;

	m_IsMatrixDirty = true;
}

void dae::Transform::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
	m_IsMatrixDirty = true;
}

glm::mat3x3 dae::Transform::CreateTranslationMatrix() const
{
	return glm::mat3x3(
		glm::vec3(1.f, 0.f, m_Translation.x),
		glm::vec3(0.f, 1.f, m_Translation.y),
		glm::vec3(0.f, 0.f, 1.f));
}

glm::mat3x3 dae::Transform::CreateRotationMatrix() const
{
	return glm::mat3x3(
		glm::vec3(glm::cos(m_Rotation), -glm::sin(m_Rotation), 0),
		glm::vec3(glm::sin(m_Rotation), glm::cos(m_Rotation), 0),
		glm::vec3(0.f, 0.f, 1.f));
}

glm::mat3x3 dae::Transform::CreateScaleMatrix() const
{
	return glm::mat3x3(
		glm::vec3(m_Scale.x, 0.f, 0.f),
		glm::vec3(0.f, m_Scale.y, 0.f),
		glm::vec3(0.f, 0.f, 1.f));
}

void dae::Transform::UpdateMatrix() const
{
	if (!m_IsMatrixDirty) 
		return;

	//m_Matrix = CreateTranslationMatrix() * CreateRotationMatrix() * CreateScaleMatrix();
	m_Matrix = CreateScaleMatrix() * CreateRotationMatrix() * CreateTranslationMatrix();

	m_IsMatrixDirty = false;
}
