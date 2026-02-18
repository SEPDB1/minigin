#pragma once

namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
	};
}