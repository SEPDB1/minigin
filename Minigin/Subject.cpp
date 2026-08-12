#include "Subject.h"
#include "IObserver.h"
#include <algorithm>

void dae::Subject::AddObserver(IObserver* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(IObserver* pObserverToRemove)
{
	auto it = std::ranges::find_if(
		m_pObservers,
		[pObserverToRemove](auto pObserver) { return pObserver == pObserverToRemove; }
	);

	if (it != m_pObservers.end())
	{
		m_pObservers.erase(it);
	}
}

void dae::Subject::Notify(std::shared_ptr<const EventArgs> pEventArgs, GameObject* pSender)
{
	for (auto pObserver : m_pObservers)
		pObserver->Notify(pEventArgs, pSender);
}