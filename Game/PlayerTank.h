#pragma once
#include <memory>
#include <vector>
#include <array>
#include "BaseComponent.h"
#include <glm/vec2.hpp>
#include <string>

namespace dae
{
	class GameObject;
	class InputDevice;
	class RenderComponent;
	class PlayerInputComponent;
	class Bullet;
	class PlayerTank : public BaseComponent
	{
	public:
		~PlayerTank() = default;
		PlayerTank(const PlayerTank& other) = delete;
		PlayerTank(PlayerTank&& other) = delete;
		PlayerTank& operator=(const PlayerTank& other) = delete;
		PlayerTank& operator=(PlayerTank&& other) = delete;

		void Start() override;
		void Update() override;
		void OnCollision(const CollisionInfo& info);

		void Shoot();

	protected:
		struct TankProperties
		{
			TankProperties() = default;
			TankProperties(const std::string& filePathTank, const std::string& filePathGun, const glm::vec2& spawnPos);

			std::string filePathTank{};
			std::string filePathGun{};
			glm::vec2 spawnPos{};
		};

		PlayerTank(GameObject* pOwner, const InputDevice* pDevice, const TankProperties& properties);
		PlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const TankProperties& properties);

	private:
		void InitialiseBulletPool();

		std::array<GameObject*, 20> m_BulletPool{};

		RenderComponent& m_pRenderCompTank;
		GameObject& m_pGunSpriteObj;
		RenderComponent& m_pRenderCompGun;
		GameObject& m_pGunBarrelObj;

		PlayerInputComponent& m_PlayerInput;
		float m_AccuTime{ 0.f };
		bool m_CanShoot{ true };

		static inline const float m_BulletSpeed{ 650.f };
		static inline const float m_ShotCooldown{ 0.12f };
	};

	class RedPlayerTank final : public PlayerTank
	{
	public:
		RedPlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos);
		RedPlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos);
		~RedPlayerTank() = default;
		RedPlayerTank(const RedPlayerTank& other) = delete;
		RedPlayerTank(RedPlayerTank&& other) = delete;
		RedPlayerTank& operator=(const RedPlayerTank& other) = delete;
		RedPlayerTank& operator=(RedPlayerTank&& other) = delete;
	};

	class BluePlayerTank final : public PlayerTank
	{
	public:
		BluePlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos);
		BluePlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos);
		~BluePlayerTank() = default;
		BluePlayerTank(const BluePlayerTank& other) = delete;
		BluePlayerTank(BluePlayerTank&& other) = delete;
		BluePlayerTank& operator=(const BluePlayerTank& other) = delete;
		BluePlayerTank& operator=(BluePlayerTank&& other) = delete;
	};

	class GreenPlayerTank final : public PlayerTank
	{
	public:
		GreenPlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos);
		GreenPlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos);
		~GreenPlayerTank() = default;
		GreenPlayerTank(const GreenPlayerTank& other) = delete;
		GreenPlayerTank(GreenPlayerTank&& other) = delete;
		GreenPlayerTank& operator=(const GreenPlayerTank& other) = delete;
		GreenPlayerTank& operator=(GreenPlayerTank&& other) = delete;
	};
}