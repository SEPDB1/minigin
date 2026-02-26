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

void dae::Transform::SetMatrix(const glm::mat3x3& matrix)
{
	m_Matrix = matrix;
}

void dae::Transform::SetPosition(float x, float y)
{
	m_Matrix[0][2] = x;
	m_Matrix[1][2] = y;
}

void dae::Transform::SetPosition(const glm::vec2& position) 
{ 
	SetPosition(position.x, position.y);
}

void dae::Transform::SetRotation(float radians)
{
	m_Rotation = radians;
	m_Matrix[0][0] = glm::cos(radians);
	m_Matrix[0][1] = -glm::sin(radians);
	m_Matrix[1][0] = glm::cos(radians);
	m_Matrix[1][1] = glm::sin(radians);
}

glm::mat3x3 dae::Transform::CreateTranslationMatrix(float x, float y)
{
	return glm::mat3x3(
		glm::vec3(1.f, 0.f, x), 
		glm::vec3(0.f, 1.f, y), 
		glm::vec3(0.f, 0.f, 1.f));
}

glm::mat3x3 dae::Transform::CreateTranslationMatrix(const glm::vec2& translation)
{
	return CreateTranslationMatrix(translation.x, translation.y);
}

glm::mat3x3 dae::Transform::CreateRotationMatrix(float radians)
{
	return glm::mat3x3(
		glm::vec3(glm::cos(radians), -glm::sin(radians), 0),
		glm::vec3(glm::sin(radians), glm::cos(radians), 0),
		glm::vec3(0.f, 0.f, 1.f));
}

glm::mat3x3 dae::Transform::CreateScaleMatrix(float x, float y)
{
	return glm::mat3x3(
		glm::vec3(x, 0.f, 0.f),
		glm::vec3(0.f, y, 0.f),
		glm::vec3(0.f, 0.f, 1.f));
}

glm::mat3x3 dae::Transform::CreateScaleMatrix(const glm::vec2& scale)
{
	return CreateScaleMatrix(scale.x, scale.y);
}