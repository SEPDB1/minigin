#include "Transform.h"

dae::Transform::Transform() = default;
//{
//	m_Matrix = glm::mat3x3(0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
//	auto val1 = m_Matrix[2][2];
//	val1 += val1;
//}

dae::Transform::~Transform() = default;

const glm::mat3x3 dae::Transform::GetMatrix() const
{
	if (m_IsMatrixDirty)
		UpdateMatrix();

	return m_Matrix;
}

glm::vec2 dae::Transform::GetPosition() const
{
	return glm::vec3(m_Matrix[0][2], m_Matrix[1][2], 0.f);
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
	m_Matrix = matrix;
}

void dae::Transform::SetPosition(float pos_x, float pos_y)
{
	m_Matrix[0][2] = pos_x;
	m_Matrix[1][2] = pos_y;
	// position can be set without transform getting dirty
}

void dae::Transform::SetPosition(const glm::vec2& position) 
{ 
	SetPosition(position.x, position.y);
}

void dae::Transform::SetRotation(float radians)
{
	m_Rotation = radians;
	m_IsMatrixDirty = true;
}

void dae::Transform::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
	m_IsMatrixDirty = true;
}

void dae::Transform::SetScale(float scale_x, float scale_y)
{
	SetScale(glm::vec2(scale_x, scale_y));
}

glm::mat3x3 dae::Transform::CreateTranslationMatrix() const
{
	return glm::mat3x3(
		glm::vec3(1.f, 0.f, m_Matrix[0][2]),
		glm::vec3(0.f, 1.f, m_Matrix[1][2]),
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
	if (!m_IsMatrixDirty) return;

	m_Matrix = CreateTranslationMatrix() * CreateRotationMatrix() * CreateScaleMatrix();
	m_IsMatrixDirty = false;
}
