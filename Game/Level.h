#pragma once
#include <memory>

namespace dae
{
	class Map;

	class Level final
	{
	public:
		Level();
		~Level();

	private:
		std::unique_ptr<Map> m_Map{};
	};
}