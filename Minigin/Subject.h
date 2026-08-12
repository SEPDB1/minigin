#pragma once
#include <memory>
#include <vector>

namespace dae
{
	class EventArgs;
	class IObserver;
	class GameObject;

	class Subject
	{
		virtual ~Subject() = default;

		void AddObserver(IObserver* pObserver);
		void RemoveObserver(IObserver* pObserver);

	protected:
		virtual void Notify(std::shared_ptr<const EventArgs> pEventArgs, GameObject* pSender);

	private:
		std::vector<IObserver*> m_pObservers{};
	};
}