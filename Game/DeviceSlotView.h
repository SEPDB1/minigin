#pragma once
#include <IObserver.h>

namespace dae
{
	class DeviceSlotView final : public IObserver
	{
		void Notify(std::shared_ptr<const EventArgs> event, GameObject* pSender) override;
	};
}