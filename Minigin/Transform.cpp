#include "Transform.h"

# define PI_F           3.1415926536f
# define PI_F_MUL_2     6.2821853072f

dae::Transform::Transform() = default;

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

glm::mat3x3 dae::Transform::Inversed() const
{
	glm::mat3x3 inv;

	const float a = m_Matrix[0][0];
	const float b = m_Matrix[0][1];
	const float tx = m_Matrix[0][2];
	const float c = m_Matrix[1][0];
	const float d = m_Matrix[1][1];
	const float ty = m_Matrix[1][2];

	const float det = a * d - b * c;
	const float invDet = 1.0f / det;

	// Inverse of the 2x2 rotation-scale block
	inv[0][0] = d * invDet;
	inv[0][1] = -b * invDet;
	inv[1][0] = -c * invDet;
	inv[1][1] = a * invDet;

	// Inverse translation
	inv[0][2] = (b * ty - d * tx) * invDet;
	inv[1][2] = (c * tx - a * ty) * invDet;

	// Last row stays the same
	inv[2][0] = 0.0f;
	inv[2][1] = 0.0f;
	inv[2][2] = 1.0f;

	return inv;
}


void dae::Transform::SetMatrix(const glm::mat3x3& matrix)
{
	m_Matrix = matrix;
	m_IsMatrixDirty = false;
}

void dae::Transform::SetPosition(float pos_x, float pos_y)
{
	SetPosition(glm::vec2(pos_x, pos_y));
}

void dae::Transform::SetPosition(const glm::vec2& position) 
{ 
	m_Translation = position;
	m_IsMatrixDirty = true;
}

void dae::Transform::SetRotation(float radians)
{
	m_Rotation = radians;

	while (radians > PI_F_MUL_2)
		m_Rotation -= PI_F;

	while (radians < -PI_F_MUL_2)
		m_Rotation += PI_F;

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
	if (!m_IsMatrixDirty) return;

	m_Matrix = CreateTranslationMatrix() * CreateRotationMatrix() * CreateScaleMatrix();
	m_IsMatrixDirty = false;
}
