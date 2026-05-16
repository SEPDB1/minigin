#include "InputDevice.h"

dae::InputDevice::InputDevice()
	: m_ID{ m_NextID++ }
{

}

dae::InputDeviceID dae::InputDevice::GetID() const
{
	return m_ID;
}