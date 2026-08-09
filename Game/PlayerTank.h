#pragma once
#include <memory>
#include <vector>
#include <array>
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class InputDevice;
	class RenderComponent;
	class PlayerInputComponent;
	class Bullet;
	class PlayerTank final : public BaseComponent
	{
	public:
		PlayerTank(GameObject* pOwner, const InputDevice* pDevice, const glm::vec2& spawnPos);
		PlayerTank(GameObject* pOwner, std::vector<const InputDevice*>&& pDevices, const glm::vec2& spawnPos);
		~PlayerTank() = default;
		PlayerTank(const PlayerTank& other) = delete;
		PlayerTank(PlayerTank&& other) = delete;
		PlayerTank& operator=(const PlayerTank& other) = delete;
		PlayerTank& operator=(PlayerTank&& other) = delete;

		void Start() override;
		void Render() const override;
		void Update() override;

		void Shoot();

	private:
		void InitialiseBulletPool();

		std::array<GameObject*, 10> m_BulletPool{};

		RenderComponent& m_pRenderCompTank;
		GameObject& m_pGunSpriteObj;
		RenderComponent& m_pRenderCompGun;
		GameObject& m_pGunBarrelObj;

		PlayerInputComponent& m_PlayerInput;
		float m_AccuTime{ 0.f };
		bool m_CanShoot{ true };

		static inline const float m_BulletSpeed{ 650.f };
		static inline const float m_ShotCooldown{ 0.3f };
	};
}