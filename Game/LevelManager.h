#pragma once
#include "BaseComponent.h"
#include <array>
#include <string>
#include <memory>

namespace dae
{
	class GameObject;
	class Level;

	class LevelManager final : public BaseComponent
	{
	public:
		LevelManager(GameObject* pOwner);
		~LevelManager();
		LevelManager(const LevelManager& other) = delete;
		LevelManager(LevelManager&& other) = delete;
		LevelManager& operator=(const LevelManager& other) = delete;
		LevelManager& operator=(LevelManager&& other) = delete;

	private:
		static const std::array<std::string, 3> m_LevelNames;
		std::unique_ptr<Level> m_pLevel;
	};
}