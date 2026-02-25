#include "Transform.h"

dae::Transform::Transform() = default;
//{
//	m_Matrix = glm::mat3x3(0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
//	auto val1 = m_Matrix[2][2];
//	val1 += val1;
//}

dae::Transform::~Transform() = default;

const glm::vec3& dae::Transform::GetPosition() const
{
	return m_Position;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& position) 
{ 
	m_Position = position; 
}

//glm::mat3x3 CreateTranslationMatrix(float x, float y, float z = 0.f)
//{
//
//}
//
//glm::mat3x3 CreateTranslationMatrix(const glm::vec3& translation)
//{
//
//}