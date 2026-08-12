#pragma once
#include <memory>
#include <vector>

namespace dae
{
	class GameObject;

	class EventArgs
	{
	public:
		virtual ~EventArgs() = default;

	protected:
		EventArgs() = default;
	};

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(std::shared_ptr<const EventArgs> event, GameObject* pSender) = 0;
	};
}